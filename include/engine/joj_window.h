#ifndef JOJWINDOW_H
#define JOJWINDOW_H

#include "core/defines.h"
#include <iostream>

enum WindowMode {FULLSCREEN, WINDOWED, BORDERLESS};

class JOJWindow
{
protected:
    u16 width;
    u16 height;
    const char* title;

    WindowMode mode;
    u16 x_pos;
    u16 y_pos;

    f32 x_center;
    f32 y_center;

    b8 running;

public:
    virtual ~JOJWindow();

    virtual b8 init() = 0;
    virtual b8 create(u16 width = 800, u16 height = 600, const char* title = "") = 0;
    virtual void show() = 0;
    virtual void run() = 0;
    virtual void destroy() = 0;

    virtual u16 get_width() const = 0;
    virtual void set_width(u16 width) = 0;

    virtual u16 get_height() const = 0;
    virtual void set_height(u16 height) = 0;

    virtual void set_size(u16 width, u16 height) = 0;
    
    virtual const char* get_title() const = 0;
    virtual void set_title(const char* title) = 0;
    
    virtual WindowMode get_mode() const = 0;
    virtual void set_mode(WindowMode mode) = 0;

    virtual u16 get_xpos() const = 0;
    virtual u16 get_ypos() const = 0;
    
    virtual f32 get_xcenter() const = 0;
    virtual f32 get_ycenter() const = 0;

    virtual b8 is_running() const = 0;
    virtual void set_running(b8 value) = 0;
};


#endif // JOJWINDOW_H