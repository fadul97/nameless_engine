#include "renderer_x11.h"

#if PLATFORM_LINUX

RendererX11::RendererX11(WindowX11* window)
{
    this->window = window;
    width = window->get_width();
    height = window->get_height();
}

RendererX11::~RendererX11() = default;

void RendererX11::draw_point(i32 x, i32 y, ul32 color)
{
    XSetForeground(window->get_display(), window->get_context(), color);
    XDrawPoint(window->get_display(), window->get_id(), window->get_context(), x, y);
}

void RendererX11::draw_line(i32 x0, i32 y0, i32 x1, i32 y1, ul32 color)
{
    XSetForeground(window->get_display(), window->get_context(), color);
    XDrawLine(window->get_display(), window->get_id(), window->get_context(), x0, y0, x1, y1);
}

void RendererX11::draw_triangle(i32 x0, i32 y0, i32 x1, i32 y1, i32 x2, i32 y2, ul32 color)
{
    draw_line(x0, y0, x1, y1, color);
    draw_line(x1, y1, x2, y2, color);
    draw_line(x2, y2, x0, y0, color);
}

#endif // RENDERER_X11_H