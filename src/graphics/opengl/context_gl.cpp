#include "context_gl.h"

#if PLATFORM_LINUX

#include "core/error_list.h"
#include <stdio.h>
#include <string.h>

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

GLContext::GLContext(WindowX11& window)
{
    this->window = &window;
    context = {0};
    fb_config = {0};
}

GLContext::~GLContext()
{
}

b8 GLContext::create()
{
    // Check GLX version
    i32 major_glx = 0;
    i32 minor_glx = 0;
    glXQueryVersion(window->get_display(), &major_glx, &minor_glx);
    if(major_glx <= 1 && minor_glx < 2)
    {
        printf("GLX 1.2 or greater is required. Current version: %d.%d.\n", major_glx, minor_glx);
        XCloseDisplay(window->get_display());
        return ERR_GC;
    }

    printf("Current GLX version: %d.%d\n", major_glx, minor_glx);
    printf("GLX client version: %s\n", glXGetClientString(window->get_display(), GLX_VERSION));
    printf("GLX client vendor: %s\n", glXGetClientString(window->get_display(), GLX_VENDOR));
    // printf("GLX client extensions: %s\t", glXGetClientString(window->get_display(), GLX_EXTENSIONS));

    printf("GLX server version: %s\n", glXQueryServerString(window->get_display(), window->get_screen_id(), GLX_VERSION));
    printf("GLX server vendor: %s\n", glXQueryServerString(window->get_display(), window->get_screen_id(), GLX_VENDOR));
    // printf("GLX server extensions: %s\t ", glXQueryServerString(window->get_display(), window->get_screen_id(), GLX_EXTENSIONS));

    // GLX, create XVisualInfo, this is the minimum visuals we want for a Modern OpenGL context
    i32 glx_attribs[] = {
        GLX_X_RENDERABLE,   True,
		GLX_DRAWABLE_TYPE,  GLX_WINDOW_BIT,
		GLX_RENDER_TYPE,    GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE,  GLX_TRUE_COLOR,
		GLX_RED_SIZE,       8,
		GLX_GREEN_SIZE,     8,
		GLX_BLUE_SIZE,      8,
		GLX_ALPHA_SIZE,     8,
		GLX_DEPTH_SIZE,     24,
		GLX_STENCIL_SIZE,   8,
		GLX_DOUBLEBUFFER,   True,
		None
    };
    
    i32 fb_count;
	GLXFBConfig* fbc = glXChooseFBConfig(window->get_display(), window->get_screen_id(), glx_attribs, &fb_count);
	if(fbc == 0)
    {
		printf("Failed to retrieve framebuffer.\n");
		XCloseDisplay(window->get_display());
		return ERR_GC;
	}
	printf("Found %d matching framebuffers.\n", fb_count);

    // Pick the FB config/visual with the most samples per pixel
	printf("Getting best XVisualInfo\n");
	i32 best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;
	for (int i = 0; i < fb_count; ++i)
    {
		XVisualInfo *temp_vi = glXGetVisualFromFBConfig(window->get_display(), fbc[i] );
		if (temp_vi != 0)
        {
			i32 samp_buf;
            i32 samples;

            glXGetFBConfigAttrib(window->get_display(), fbc[i], GLX_SAMPLE_BUFFERS, &samp_buf);
			glXGetFBConfigAttrib(window->get_display(), fbc[i], GLX_SAMPLES       , &samples);

            //std::cout << "  Matching fbconfig " << i << ", SAMPLE_BUFFERS = " << samp_buf << ", SAMPLES = " << samples << ".";

			if(best_fbc < 0 || (samp_buf && samples > best_num_samp))
            {
				best_fbc = i;
				best_num_samp = samples;
			}

			if(worst_fbc < 0 || !samp_buf || samples < worst_num_samp)
				worst_fbc = i;

			worst_num_samp = samples;
		}
		XFree(temp_vi);
	}

    printf("Best visual info index: %d.\n", best_fbc);
    fb_config = fbc[best_fbc];
    XFree(fbc);

    window->set_visual(glXGetVisualFromFBConfig(window->get_display(), fb_config));
    if(window->get_visual() == 0)
    {
        printf("Failed to create correct visual window.\n");
        XCloseDisplay(window->get_display());
        return ERR_GC;
    }

    if(window->get_screen_id() != window->get_visual()->screen)
    {
		printf("screen_id(%d) does not match visual->screen(%d).\n", window->get_screen_id(), window->get_visual()->screen);
		XCloseDisplay(window->get_display());
		return ERR_GC;
	}

    return OK;
}

void GLContext::make_current()
{
    // Create GLX OpenGL Context
    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
	glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddressARB((const GLubyte *) "glXCreateContextAttribsARB");

    const char *glx_exts = glXQueryExtensionsString(window->get_display(), window->get_screen_id());
	// printf("Late extensions: %s\t", glx_exts);
	if(glXCreateContextAttribsARB == 0)
		printf("glXCreateContextAttribsARB() not found.");

    i32 context_attribs[] = {
		GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
		GLX_CONTEXT_MINOR_VERSION_ARB, 2,
		GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
		None
	};

    context = 0;
    if(!is_extension_supported(glx_exts, "GLX_ARB_create_context"))
		context = glXCreateNewContext(window->get_display(), fb_config, GLX_RGBA_TYPE, 0, True);
	else
		context = glXCreateContextAttribsARB(window->get_display(), fb_config, 0, TRUE, context_attribs);
	XSync(window->get_display(), False);

    // Verifying that context is a direct context
	if(!glXIsDirect(window->get_display(), context)) {
		printf("Indirect GLX rendering context obtained\n");
	}
	else {
		printf("Direct GLX rendering context obtained\n");
	}

    glXMakeCurrent(window->get_display(), window->get_id(), context);

	i32 version = gladLoadGL((GLADloadfunc) glXGetProcAddress);
    printf("Current GL loaded: %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

	printf("GL Renderer: %s\n", glGetString(GL_RENDERER));
	printf("GL Version: %s\n", glGetString(GL_VERSION));
	printf("GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void GLContext::destroy()
{
    // Cleanup GLX
	glXDestroyContext(window->get_display(), context);
}

b8 GLContext::is_extension_supported(const char *ext_list, const char *extension){
	const char *start;
	const char *where, *terminator;

	/* Extension names should not have spaces. */
	where = strchr(extension, ' ');
	if (where || *extension == '\0')
		return FALSE;

	/* It takes a bit of care to be fool-proof about parsing the
	 OpenGL extensions string. Don't be fooled by sub-strings,
	 etc. */
	for (start=ext_list;;) {
		where = strstr(start, extension);

		if (!where) {
			break;
		}

		terminator = where + strlen(extension);

		if ( where == start || *(where - 1) == ' ' ) {
			if ( *terminator == ' ' || *terminator == '\0' ) {
				return TRUE;
			}
		}	

		start = terminator;
	}

	return FALSE;
}

#endif // PLATFORM_LINUX