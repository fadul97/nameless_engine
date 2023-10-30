#include "engine/joj_engine.h"

#include <iostream>
#include "core/error_list.h"
#include <unistd.h>

double get_abs_time()
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC_RAW, &now);
    return now.tv_sec + now.tv_nsec * 0.000000001;
}

const d64 TARGET_FRAME_TIME = 1.0 / 60.0; // 60 FPS

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

b8 NamelessEngine::init(u16 width, u16 height, const char* title)
{
    window = new WindowX11();
    context = new GLContext(*window);
    input = new InputX11();

    b8 result = window->init();
    if(result != OK)
    {
        std::cout << "Failed to initialize window - " << "[" << error_names[result] << "]\n";
        return result;
    }

    result = context->create();
    if(result != OK)
    {
        std::cout << "Failed to create context - " << "[" << error_names[result] << "]\n";
        return result;
    }

    result = window->create(width, height, title);
    if(result != OK)
    {
        std::cout << "Failed to create window - " << "[" << error_names[result] << "]\n";
        return result;
    }
    
    context->make_current();

    window->show();

    return OK;
}

void NamelessEngine::run()
{
    XEvent ev;
    char str[25];
    KeySym keysym;
    Keys key;

    f32 delta_time = 0.0f;              // Time between current frame and last frame
    f32 last_frame = get_abs_time();
    f32 current_frame;

    d64 accumulated_time = 0.0f;

    while(window->is_running())
    {
        // FIXME: delta_time is not working properly
        current_frame = get_abs_time();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;

        accumulated_time += delta_time;

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

                        if(key == KEY_ESCAPE)
                            window->set_running(false);

                        if(key == KEY_SPACE)
                            std::cout << "KEY_SPACE pressed!\n";
                        
                        if(key == KEY_ENTER)
                            std::cout << "KEY_ENTER pressed!\n";
                        
                        if(key == KEY_NUMPAD_ENTER)
                            std::cout << "KEY_NUMPAD_ENTER pressed!\n";
                    }
                } break;
                case LeaveNotify:
                case EnterNotify:
                    break;
                case MotionNotify: {
                    input->update_mouse_position(ev.xmotion.x, ev.xmotion.y);
                    std::cout << "Mouse: " << input->get_mouse_x() << "x" << input->get_mouse_y() << "\n";
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

        // std::cout << "OUTSIDE LOOP:\n";
        // std::cout << "Accumulated time = " << accumulated_time << "\n";
        // std::cout << "TARGET_FRAME_TIME = " << TARGET_FRAME_TIME << "\n\n";
        while(accumulated_time >= TARGET_FRAME_TIME)
        {
            // std::cout << "\tINSIDE LOOP:\n";
            // std::cout << "\tAccumulated time = " << accumulated_time << "\n";
            // std::cout << "\tTARGET_FRAME_TIME = " << TARGET_FRAME_TIME << "\n\n";
            accumulated_time -= TARGET_FRAME_TIME;
        }
    
        d64 time_to_sleep = TARGET_FRAME_TIME - (get_abs_time() - current_frame);
        if(time_to_sleep > 0)
            usleep(time_to_sleep);
        
        // glXSwapBuffers(window->get_display(), window->get_id());

        // If we sync, it will take 2 esc key presses to close window
        //      -> It takes longer to recognize key press
        XSync(window->get_display(), false);
        if (XPending(window->get_display()) == 0)
            usleep(1000); 
    }

    XFlush(window->get_display());
}

void NamelessEngine::shutdown()
{
    context->destroy();
    window->destroy();
}
