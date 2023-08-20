#ifndef WINDOW_X11_H
#define WINDOW_X11_H

#include "defines.h"

#if PLATFORM_LINUX

#include <X11/Xlib.h>
#include <time.h>
#include <X11/Xutil.h>

#include "input_x11.h"

class WindowX11
{
private:
    Display* display;
    u32 id;
    Screen* screen;
    i32 screen_id;
    XSetWindowAttributes x_window_attribs;
    XVisualInfo* visual;
    ul32 delete_msg;

    const char* title;
    i16 width;
    i16 height;
    b8 running;

    InputX11* input;

    GC gc;

public:
    WindowX11();
    ~WindowX11();

    b8 init();
    b8 create(const char* title = "", i16 width = 800, i16 height = 600);
    b8 init_create_glx_window(const char* title = "", i16 width = 800, i16 height = 600);
    void show();
    void run();
    void destroy();

    Display* get_display() const;
    u32 get_id() const;
    i32 get_screen_id() const;
    XVisualInfo* get_visual() const;
    ul32 get_delete_msg() const;
    const GC& get_context() const;
    b8 is_running() const;
    void set_running(b8 value);
    void set_visual(XVisualInfo* visual);
};

inline Display* WindowX11::get_display() const
{ return display; }

inline u32 WindowX11::get_id() const
{ return id; }

inline i32 WindowX11::get_screen_id() const
{ return screen_id; }

inline XVisualInfo* WindowX11::get_visual() const
{ return visual; }

inline ul32 WindowX11::get_delete_msg() const
{ return delete_msg; }

inline const GC& WindowX11::get_context() const
{ return gc; }

inline b8 WindowX11::is_running() const
{ return running; }

inline void WindowX11::set_running(b8 value)
{ running = value; }

inline void WindowX11::set_visual(XVisualInfo* visual)
{ this->visual = visual; }

#endif // KPLATFORM_LINUX

#endif // WINDOW_X11_H