#ifndef NML_ENGINE_H
#define NML_ENGINE_H

#include "defines.h"

#if PLATFORM_LINUX

#include "window_x11.h"
#include "context_gl.h"
#include "input_x11.h"

class NamelessEngine
{
private:
    WindowX11* window;
    GLContext* context;
    InputX11* input;
    
public:
    NamelessEngine();
    ~NamelessEngine();

    b8 init(const char* title, i16 width, i16 height);
    void run();
    void shutdown();
};

#endif // PLATFORM_LINUX

#endif // NML_ENGINE_H