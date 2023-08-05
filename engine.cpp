#include "engine.h"

#include <iostream>
#include "error_list.h"
#include <unistd.h>

NamelessEngine::NamelessEngine()
{
    window = nullptr;
    context = nullptr;
    input = nullptr;
}

NamelessEngine::~NamelessEngine()
{
    delete input;
    delete context;
    delete window;
}

b8 NamelessEngine::init(const char* title, i16 width, i16 height)
{
    window = new WindowX11();
    context = new GLContext(*window);
    input = new InputX11();

    b8 result = window->init();
    if(result != OK)
    {
        std::cout << "Failed to initalize window - " << "[" << error_names[result] << "]\n";
        return result;
    }

    result = context->create();
    if(result != OK)
    {
        std::cout << "Failed to create context - " << "[" << error_names[result] << "]\n";
        return result;
    }

    result = window->create(title, width, height);
    if(result != OK)
    {
        std::cout << "Failed to create window - " << "[" << error_names[result] << "]\n";
        return result;
    }

    context->make_current();
    window->show();

    return OK;
}

void NamelessEngine::run(App* app)
{
    XEvent ev;
    char str[25];
    KeySym keysym;
    Keys key;

    app->set_input(input);
    app->init();

    while(window->is_running())
    {
        if(XPending(window->get_display()) > 0)
        {

            XNextEvent(window->get_display(), &ev);

            switch(ev.type)
            {
                case ButtonRelease:
                case ButtonPress: {
                    b8 button_pressed = ev.type == ButtonPress;
                    Buttons mouse_button = MAX_BUTTONS;
                    switch(ev.xbutton.button)
                    {
                        case 1:
                            mouse_button = BUTTON_LEFT;
                            std::cout << "BUTTON_LEFT clicked!\n";
                            break;
                        case 2:
                            mouse_button = BUTTON_MIDDLE;
                            std::cout << "BUTTON_MIDDLE clicked!\n";
                            break;
                        case 3:
                            mouse_button = BUTTON_RIGHT;
                            std::cout << "BUTTON_RIGHT clicked!\n";
                            break;
                    }
                    if(mouse_button != MAX_BUTTONS)
                    {
                        input->process_button(mouse_button, button_pressed);
                        input->update();
                    }
                } break;

                case KeyRelease:
                case KeyPress:{
                    u32 len = XLookupString(&ev.xkey, str, 25, &keysym, NULL);
                    if(len > 0){
                        b8 pressed = ev.type == KeyPress;
                        key = input->translate_keycode(keysym);
                        input->process_key(key, pressed);
                        input->update();

                        if(key == KEY_SPACE)
                            std::cout << "KEY_SPACE clicked!\n";
                        
                        if(key == KEY_ENTER)
                            std::cout << "KEY_ENTER clicked!\n";

                        if(key == KEY_ESCAPE)
                            window->set_running(false);
                    }
                } break;
                case LeaveNotify:
                case EnterNotify:
                    break;
                case MotionNotify: {
                    input->update_mouse_position(ev.xmotion.x, ev.xmotion.y);
                } break;
                case ConfigureNotify:
                    break;
                case ClientMessage:{
                    if (ev.xclient.data.l[0] == window->get_delete_msg()) {
                        window->set_running(false);
                    }
                } break;
                case DestroyNotify:
                    break;
            }
        }

        app->update(1.0f);

        app->draw();

        glClearColor(0.1, 0.2, 0.9, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
       
        glXSwapBuffers(window->get_display(), window->get_id());

        // If we sync, it will take 2 esc key presses to close window
        //      -> It takes longer to recognize key press
        XSync(window->get_display(), false);
        if (XPending(window->get_display()) == 0)
            usleep(1000); 
    }

    app->shutdown();

    XFlush(window->get_display());
}

void NamelessEngine::shutdown()
{
    context->destroy();
    window->destroy();
}
