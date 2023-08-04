#ifndef WINDOW_X11_H
#define WINDOW_X11_H

#include "defines.h"

#if PLATFORM_LINUX

#include <X11/Xlib.h>
#include <time.h>
#include <X11/Xutil.h>

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

public:
    WindowX11();
    ~WindowX11();

    b8 init();
    b8 create(const char* title = "", i16 width = 800, i16 height = 600);
    void show();
    void run();
    void destroy();

    Display* get_display() const;
    u32 get_id() const;
    i32 get_screen_id() const;
    XVisualInfo* get_visual() const;
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

inline void WindowX11::set_visual(XVisualInfo* visual)
{ this->visual = visual; }

#endif // KPLATFORM_LINUX

#endif // WINDOW_X11_H