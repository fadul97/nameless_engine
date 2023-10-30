#ifndef CONTEXT_GL_H
#define CONTEXT_GL_H

#include "core/defines.h"

// FIXME:
#include "../context.h"

#if PLATFORM_LINUX

// #include "include/window_x11.h"
// FIXME: 
#include "../../../platform/x11/include/window_x11.h"

#define GLAD_GLX_NO_X11
#include <glad/gl.h> // File is on system
#include <GL/glx.h>

class GLContext : public Context
{
private:
    GLXContext context;
    GLXFBConfig fb_config;
    WindowX11* window;

    b8 is_extension_supported(const char *ext_list, const char *extension);

public:
    GLContext(WindowX11& window);
    ~GLContext();

    b8 create();
    void make_current();
    void destroy();
};

#endif // PLATFORM_LINUX

#endif // CONTEXT_GL_H