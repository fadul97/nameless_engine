#ifndef JOJ_ENGINE_H
#define JOJ_ENGINE_H

#include "core/defines.h"

#if PLATFORM_LINUX

// #include "window_x11.h"
// FIXME:
#include "platform/x11/include/window_x11.h"


// #include "context_gl.h"
// FIXME:
#include "graphics/opengl/context_gl.h"

// #include "input_x11.h"
// FIXME:
#include "platform/x11/include/input_x11.h"

#include "core/error_list.h"

class NamelessEngine
{
private:
    WindowX11* window;
    GLContext* context;
    InputX11* input;

public:
    NamelessEngine();
    ~NamelessEngine();

    b8 init(u16 width, u16 height, const char* title);
    void run();
    void shutdown();
};

#endif // PLATFORM_LINUX

#endif // JOJ_ENGINE_H