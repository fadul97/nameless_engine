#ifndef NML_ENGINE_H
#define NML_ENGINE_H

#include "defines.h"

#if PLATFORM_LINUX

#include "window_x11.h"
#include "context_gl.h"
#include "renderer_x11.h"
#include "input_x11.h"
#include "error_list.h"
#include "app.h"

typedef enum
{
    RENDERER_GLX,
    RENDERER_OPENGL
} BackendRenderer;

class NamelessEngine
{
private:
    WindowX11* window;
    GLContext* context;
    InputX11* input;

    BackendRenderer backend_rederer;
    RendererX11* renderer;
    
public:
    NamelessEngine(BackendRenderer backend_renderer = RENDERER_OPENGL);
    ~NamelessEngine();

    b8 init(const char* title, i16 width, i16 height);
    void run(App* app);
    void shutdown();

    RendererX11* get_renderer() const;
};

inline RendererX11* NamelessEngine::get_renderer() const
{ return renderer; }

#endif // PLATFORM_LINUX

#endif // NML_ENGINE_H