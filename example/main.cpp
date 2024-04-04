#include <SDL2/SDL.h>

#include <GL/gl.h>
#include <GL/glx.h>

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
        const std::function<void(SDL_GLContext *)> gl_context_destructor = [](SDL_GLContext *context)
        {
            SDL_GL_DeleteContext(context);
        };

        _window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>>(
            SDL_CreateWindow(file.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL),
            window_destructor);
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

    void init_slices()
    {
        SDL_GL_MakeCurrent(_window.get(), _gl_context.get());
    }

    void draw_slice()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
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

private:
    // SDL data
    std::unique_ptr<SDL_Window, std::function<void(SDL_Window *)>> _window;
    std::unique_ptr<SDL_GLContext, std::function<void(SDL_GLContext *)>> _gl_context;

    // image info
    std::string _image_path;
    std::vector<GLuint> _image_slices;

    // state information
    int _current_slice;
    int _last_slice;
};

int main(int argc, const char **argv)
{
    std::unique_ptr<nifti_viewer> viewer;
    bool running;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    running = true;

    while (running)
    {
        if (SDL_PollEvent(&event) > 0)
        {
        }
    }

    SDL_Quit();
    return 0;
}