#include "include/window_x11.h"

#include "core/error_list.h"
#include <unistd.h>
#include "engine/keys.h"
#include <GL/glx.h>

WindowX11::WindowX11(u16 width, u16 height, const char* title)
{
    display = nullptr;
    id = 0;
    screen = {0};
    screen_id = 0;
    x_window_attribs = {0};
    visual = {0};
    delete_msg = 0;

    running = false;

    input = new InputX11();

    gc = {0};
}

WindowX11::~WindowX11(){}

b8 WindowX11::init()
{
    // Open display
    display = XOpenDisplay(NULL);
    if(display == NULL)
    {
        std::cout << "Failed to open display\n";
        return ERR_WINDOW;
    }

    // Setup screen
    screen = DefaultScreenOfDisplay(display);
    screen_id = DefaultScreen(display);

    return OK;
}

b8 WindowX11::create(u16 width, u16 height, const char* title)
{
    // Set window attributes
    x_window_attribs.border_pixel = BlackPixel(display, screen_id);
    x_window_attribs.background_pixel = WhitePixel(display, screen_id);
    x_window_attribs.override_redirect = True;
    x_window_attribs.colormap = XCreateColormap(display, RootWindow(display, screen_id), visual->visual, AllocNone);
    x_window_attribs.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask | KeymapStateMask
                                | StructureNotifyMask | ButtonPressMask | ButtonReleaseMask
                                | EnterWindowMask | LeaveWindowMask | PointerMotionMask
                                | FocusChangeMask;
    
    this->width = width;
    this->height = height;
    this->title = title;

    // Create window
    id = XCreateWindow(
            display,
            RootWindow(display, screen_id),
            0,
            0,
            width,
            height,
            0,
            visual->depth,
            InputOutput,
            visual->visual,
            CWBackPixel | CWColormap | CWBorderPixel | CWEventMask,
            &x_window_attribs);
    
    if(id == 0)
    {
        std::cout << "Failed to create window.\n";
        XCloseDisplay(display);
        return ERR_WINDOW;
    }

    // TODO: XWindowAttribs and XSelectInput?
    // Set Input
    // XSelectInput(display, id, ExposureMask  | KeyPressMask | KeyReleaseMask | KeymapStateMask
    //                                         | StructureNotifyMask | ButtonPressMask | ButtonReleaseMask
    //                                         | EnterWindowMask | LeaveWindowMask | PointerMotionMask
    //                                         | FocusChangeMask);

    // Name Window
    XStoreName(display, id, title);

    // Redirect Close
	delete_msg = XInternAtom(display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(display, id, &delete_msg, 1);

    return OK;
}

b8 WindowX11::init_create_glx_window(const char* title, i16 width, i16 height)
{
    // Open display
    display = XOpenDisplay(NULL);
    if(display == NULL)
    {
        std::cout << "Failed to open display\n";
        return ERR_WINDOW;
    }

    screen_id = DefaultScreen(display);

    ul32 black = BlackPixel(display, 0);
    ul32 white = WhitePixel(display, 0);
    // ul32 red = RGB(255, 0, 0);
    // ul32 blue = RGB(0, 0, 255);

    id = XCreateSimpleWindow(
        display,
        DefaultRootWindow(display),
        0, 0,
        width, height,
        5,
        white,
        black);

    if(id == 0)
    {
        std::cout << "Failed to create window.\n";
        XCloseDisplay(display);
        return ERR_WINDOW;
    }

    this->width = width;
    this->height = height;
    this->title = title;

    XStoreName(display, id, title);

    XSelectInput(display, id,
                ExposureMask | KeyPressMask | KeyReleaseMask | KeymapStateMask
                | StructureNotifyMask | ButtonPressMask | ButtonReleaseMask
                | EnterWindowMask | LeaveWindowMask | PointerMotionMask
                | FocusChangeMask);

    gc = XCreateGC(display, id, 0, 0);

    XSetBackground(display, gc, white);
    XSetForeground(display, gc, white);

    // Redirect Close
    delete_msg = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, id, &delete_msg, 1);

    XClearWindow(display, id);
    XMapRaised(display, id);

    return OK;
}

void WindowX11::show()
{
    // So frame doesn't stutter when holding key
    XAutoRepeatOff(display);

    // Show window
	XClearWindow(display, id);
	XMapRaised(display, id);
    
    // Sync to update window info
    XSync(display, id);

    // Keep window open
    running = true;
}

void WindowX11::run()
{
    XEvent ev;
    char str[25];
    KeySym keysym;
    Keys key;

    while(running)
    {
        if(XPending(display) > 0)
        {

            XNextEvent(display, &ev);

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
                            running = false;
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
                    if (ev.xclient.data.l[0] == delete_msg) {
                        running = false;
                    }
                } break;
                case DestroyNotify:
                    break;
            }
        }
       
        glXSwapBuffers(display, id);

        // If we sync, it will take 2 esc key presses to close window
        //      -> It takes longer to recognize key press
        XSync(display, false);
        if (XPending(display) == 0)
            usleep(1000); 
    }

    XFlush(display);
}

void WindowX11::destroy()
{
    XAutoRepeatOn(display);

    if(id)
        XDestroyWindow(display, id);
    
    if(display)
        XCloseDisplay(display);
}