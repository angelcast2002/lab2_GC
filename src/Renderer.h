#pragma once

#include <SDL.h>

class Renderer {
public:
    Renderer(SDL_Window* window);
    ~Renderer();

    void present();

    SDL_Renderer* getRenderer() const { return renderer; }

private:
    SDL_Renderer* renderer;
};
