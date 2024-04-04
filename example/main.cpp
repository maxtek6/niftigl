#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <niftigl.hpp>

#include <functional>
#include <memory>
#include <string>

class nifti_viewer
{
public:
    nifti_viewer(const std::string &file)
    {
        const std::function<void(SDL_Window *)> window_destructor = [](SDL_Window *window)
        {
            SDL_DestroyWindow(window);
        };
        const std::function<void(SDL_GLContext)> gl_context_destructor = [](SDL_GLContext context)
        {
            SDL_GL_DeleteContext(context);
        };

        _window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>>(
            SDL_CreateWindow(file.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL),
            window_destructor);

        _gl_context = std::unique_ptr<void, std::function<void(SDL_GLContext)>>(SDL_GL_CreateContext(_window.get()), gl_context_destructor);

        SDL_GL_MakeCurrent(_window.get(), _gl_context.get());

        niftigl::stage(file, _image_slices);

        _current_slice = 0;
        _last_slice = _image_slices.size() - 1;
    }

    ~nifti_viewer()
    {
        if (_image_slices.size() > 0)
        {
            glDeleteTextures(_image_slices.size(), _image_slices.data());
        }
    }

    void next_slice()
    {
        if (_current_slice == _last_slice)
        {
            _current_slice = 0;
        }
        else
        {
            _current_slice++;
        }
    }

    void prev_slice()
    {
        if (_current_slice == 0)
        {
            _current_slice = _last_slice;
        }
        else
        {
            _current_slice--;
        }
    }

    void draw_slice()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glBindTexture(GL_TEXTURE_2D, _image_slices[_current_slice]);
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex2f(-1, 1);
        glTexCoord2f(1, 0);
        glVertex2f(1, -1);
        glTexCoord2f(1, 1);
        glVertex2f(1, 1);
        glTexCoord2f(0, 1);
        glVertex2f(-1, 1);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        SDL_GL_SwapWindow(_window.get());
    }

    bool active() const
    {
        return _active;
    }

    void quit()
    {
        _active = false;
    }

private:
    // SDL data
    std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>> _window;
    std::unique_ptr<void, std::function<void(SDL_GLContext)>> _gl_context;

    // image info
    std::vector<GLuint> _image_slices;

    // state information
    int _current_slice;
    int _last_slice;
    bool _active;
};

static void handle_keydown(std::unique_ptr<nifti_viewer> &viewer, const SDL_KeyboardEvent *event)
{
    if (event->repeat == 0)
    {
        switch (event->keysym.scancode)
        {
        case SDL_SCANCODE_LEFT:
            viewer->prev_slice();
            break;
        case SDL_SCANCODE_RIGHT:
            viewer->next_slice();
            break;
        case SDL_SCANCODE_ESCAPE:
            viewer->quit();
            break;
        }
    }
}

int main(int argc, const char **argv)
{
    std::unique_ptr<nifti_viewer> viewer;
    bool running;
    SDL_Event event;

    if (argc > 1)
    {
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

        viewer = std::make_unique<nifti_viewer>(argv[1]);

        running = true;

        while (running)
        {
            if (SDL_PollEvent(&event) > 0)
            {
                switch (event.type)
                {
                case SDL_KEYDOWN:
                    handle_keydown(viewer, &event.key);
                    break;
                case SDL_QUIT:
                    viewer->quit();
                }
            }
            viewer->draw_slice();
        }

        SDL_Quit();
    }
    return 0;
}