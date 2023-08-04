#include "window_x11.h"

#if PLATFORM_LINUX

#include <iostream>
#include <unistd.h>
#include "error_list.h"
#include "context_gl.h"


WindowX11::WindowX11()
{
    display = nullptr;
    id = 0;
    screen = {0};
    screen_id = 0;
    x_window_attribs = {0};
    visual = {0};
    delete_msg = 0;

    title = "";
    width = 0;
    height = 0;
    running = false;
}

WindowX11::~WindowX11()
{
    // XAutoRepeatOn(display);
}

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

b8 WindowX11::create(const char* title, i16 width, i16 height)
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
        std::cout << "Failed to create window\n";
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

    while(running)
    {
        if(XPending(display) > 0)
        {

            XNextEvent(display, &ev);

            switch(ev.type)
            {
                case ButtonRelease:
                case ButtonPress: {
                } break;

                case KeyRelease:
                case KeyPress:{
                } break;
                case LeaveNotify:
                case EnterNotify:
                    break;
                case MotionNotify: {
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

        glClearColor(0.1, 0.2, 0.9, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
       
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

#endif // PLATFORM_LINUX