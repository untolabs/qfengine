#include "client/precompiled.hh"
#include "client/opengl/opengl.hh"

#include "core/assert.hh"
#include "core/cmdline.hh"
#include "core/logging.hh"

#include "shared/game.hh"

#include "client/globals.hh"

static SDL_GLContext gl_context;

static void GLAD_API_PTR on_opengl_message(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *param)
{
    QF_inform("opengl: %s", message);
}

void opengl::video_init(void)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    char fmt_buffer[256];
    stbsp_snprintf(fmt_buffer, sizeof(fmt_buffer), "%s - OpenGL", shared_game::window_title);
    QF_verbose("opengl: window title: %s", fmt_buffer);

    globals::window = SDL_CreateWindow(fmt_buffer, 640, 480, SDL_WINDOW_OPENGL);
    QF_assert_msg(globals::window, SDL_GetError());

    gl_context = SDL_GL_CreateContext(globals::window);
    QF_assert_msg(gl_context, SDL_GetError());

    SDL_GL_MakeCurrent(globals::window, gl_context);

    if(!gladLoadGL(reinterpret_cast<GLADloadfunc>(&SDL_GL_GetProcAddress))) {
        QF_throw("opengl: unable to resolve OpenGL function pointers");
    }

    if(GLAD_GL_KHR_debug) {
        if(!cmdline::contains("opengl-quiet")) {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(&on_opengl_message, nullptr);

            // This is an NVIDIA-specific thing; whenever something
            // is done to a buffer object, the driver just decides to
            // fill the debug callback up with clutter about memory usage
            static const std::uint32_t ignore_nvidia_131185 = 131185;
            glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_OTHER, GL_DONT_CARE, 1, &ignore_nvidia_131185, GL_FALSE);
        }
        else {
            QF_notice("opengl: GL_KHR_debug is available but was disabled");
            QF_notice("opengl: OpenGL errors will not be logged");
        }
    }
    else {
        QF_warning("opengl: GL_KHR_debug is not available");
        QF_warning("opengl: OpenGL errors will not be logged");
    }

    QF_inform("opengl: GL_VERSION: %s", glGetString(GL_VERSION));
    QF_inform("opengl: GL_RENDERER: %s", glGetString(GL_RENDERER));
}

void opengl::video_deinit(void)
{
    SDL_GL_DestroyContext(gl_context);
    SDL_DestroyWindow(globals::window);

    globals::window = nullptr;
    gl_context = nullptr;
}

void opengl::video_prepare(void)
{
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void opengl::video_present(void)
{
    SDL_GL_SwapWindow(globals::window);
}
