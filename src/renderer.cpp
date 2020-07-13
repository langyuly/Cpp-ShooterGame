#include "renderer.h"

#include <SDL_image.h>

#include <iostream>
#include <string>

#include "movingobject.h"
#include "tank.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create Window
    sdl_window = SDL_CreateWindow("Shooter Game", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, screen_width,
                                  screen_height, SDL_WINDOW_SHOWN);

    if (nullptr == sdl_window) {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == sdl_renderer) {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    //surface = SDL_LoadBMP("../img/ball.bmp");
    SDL_Surface *tank_surface = IMG_Load("../img/tank.png");
    if (!tank_surface) {
        std::cerr << "Surface could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }
    tank_tex = SDL_CreateTextureFromSurface(sdl_renderer, tank_surface);
    if (!tank_tex) {
        std::cerr << "Texture could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }
    SDL_FreeSurface(tank_surface);

    SDL_Surface *bullet_surface = IMG_Load("../img/bullet.png");
    if (!bullet_surface) {
        std::cerr << "Surface could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }
    bullet_tex = SDL_CreateTextureFromSurface(sdl_renderer, bullet_surface);
    if (!bullet_tex) {
        std::cerr << "Texture could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }
    SDL_FreeSurface(bullet_surface);

    SDL_Surface *spaceship_surface = IMG_Load("../img/spaceship.png");
    if (!spaceship_surface) {
        std::cerr << "Surface could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }
    spaceship_tex = SDL_CreateTextureFromSurface(sdl_renderer, spaceship_surface);
    if (!spaceship_tex) {
        std::cerr << "Texture could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }
    SDL_FreeSurface(spaceship_surface);
}

Renderer::~Renderer() {
    SDL_DestroyTexture(tank_tex);
    SDL_DestroyTexture(bullet_tex);
    SDL_DestroyTexture(spaceship_tex);
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void Renderer::Render(Tank const tank, std::vector<MovingObject> &bullets,
                      std::vector<MovingObject> &spaceships) {
    SDL_Rect block;
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;

    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Render tank
    block.x = static_cast<int>(tank.GetPositionX() * block.w);
    block.y = static_cast<int>(tank.GetPositionY() * block.h);
    SDL_RenderCopy(sdl_renderer, tank_tex, NULL, &block);

    // Render bullets
    for (int i = 0; i < bullets.size(); i++) {
        block.x = static_cast<int>(bullets[i].GetPositionX() * block.w);
        block.y = static_cast<int>(bullets[i].GetPositionY() * block.h);
        SDL_RenderCopy(sdl_renderer, bullet_tex, NULL, &block);
    }

    // Render spaceships
    for (int j = 0; j < spaceships.size(); j++) {
        block.x = static_cast<int>(spaceships[j].GetPositionX() * block.w);
        block.y = static_cast<int>(spaceships[j].GetPositionY() * block.h);
        SDL_RenderCopy(sdl_renderer, spaceship_tex, NULL, &block);
    }

    // Update Screen
    SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
    std::string title{"Shooter Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
    SDL_SetWindowTitle(sdl_window, title.c_str());
}
