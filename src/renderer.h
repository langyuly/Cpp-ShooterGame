#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "SDL.h"

class Tank;
class MovingObject;

class Renderer {
   public:
    Renderer(const std::size_t screen_width, const std::size_t screen_height,
             const std::size_t grid_width, const std::size_t grid_height);
    ~Renderer();

    void Render(Tank const &tank, std::vector<MovingObject> const &bullets,
                std::vector<MovingObject> const &spaceships);
    void UpdateWindowTitle(int score, int fps);

   private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;

    SDL_Texture *tank_tex;
    SDL_Texture *bullet_tex;
    SDL_Texture *spaceship_tex;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;
};

#endif