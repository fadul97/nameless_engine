#ifndef WINDOW_X11_H
#define WINDOW_X11_H

// #if PLATFORM_LINUX

#include "engine/joj_window.h"

#include <X11/Xlib.h>
#include <time.h>
#include <X11/Xutil.h>
#include "input_x11.h"

class WindowX11 : public JOJWindow
{
private:
    u32 id;
    Display* display;
    Screen* screen;
    i32 screen_id;
    XSetWindowAttributes x_window_attribs;
    XVisualInfo* visual;
    ul32 delete_msg;

    b8 running;

    GC gc;

    InputX11* input;

public:
    WindowX11(u16 width = 800, u16 height = 600, const char* title = "");
    ~WindowX11();

    b8 init();
    b8 create(u16 width = 800, u16 height = 600, const char* title = "");
    b8 init_create_glx_window(const char* title = "", i16 width = 800, i16 height = 600);
    void show();
    void run();
    void destroy();

    u16 get_width() const;
    void set_width(u16 width);

    u16 get_height() const;
    void set_height(u16 height);

    void set_size(u16 width, u16 height);

    const char* get_title() const;
    void set_title(const char* title);

    WindowMode get_mode() const;
    void set_mode(WindowMode mode);

    u16 get_xpos() const;
    u16 get_ypos() const;
    
    f32 get_xcenter() const;
    f32 get_ycenter() const;

    b8 is_running() const;
    void set_running(b8 value);

    const u32& get_id() const;
    Display* get_display() const;
    i32 get_screen_id() const;
    XVisualInfo* get_visual() const;
    ul32 get_delete_msg() const;
    const GC& get_context() const;

    void set_visual(XVisualInfo* visual);
};

inline u16 WindowX11::get_width() const 
{ return width; }

inline void WindowX11::set_width(u16 width)
{ this->width = width; }

inline u16 WindowX11::get_height() const 
{ return height; }

inline void WindowX11::set_height(u16 height)
{ this->height = height; }

inline void WindowX11::set_size(u16 width, u16 height)
{ this->width = width; this->height = height; }

inline const char* WindowX11::get_title() const 
{ return title; }

inline void WindowX11::set_title(const char* title)
{ this->title = title; }

inline WindowMode WindowX11::get_mode() const
{ return mode; }

inline void WindowX11::set_mode(WindowMode mode)
{ this->mode = mode; }

inline u16 WindowX11::get_xpos() const
{return x_pos; }

inline u16 WindowX11::get_ypos() const
{ return y_pos; }

inline f32 WindowX11::get_xcenter() const
{ return x_center; }

inline f32 WindowX11::get_ycenter() const
{return y_center; }

inline b8 WindowX11::is_running() const
{ return running; }

inline void WindowX11::set_running(b8 value)
{ running = value; }

inline const u32& WindowX11::get_id() const
{ return id; }

inline Display* WindowX11::get_display() const
{ return display; }

inline i32 WindowX11::get_screen_id() const
{ return screen_id; }

inline XVisualInfo* WindowX11::get_visual() const
{ return visual; }

inline ul32 WindowX11::get_delete_msg() const
{ return delete_msg; }

inline const GC& WindowX11::get_context() const
{ return gc; }

inline void WindowX11::set_visual(XVisualInfo* visual)
{ this->visual = visual; }

// #endif // PLATFORM_LINUX

#endif // WINDOW_X11_H