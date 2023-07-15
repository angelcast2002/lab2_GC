#include "Renderer.h"

Renderer::Renderer(SDL_Window* window) {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(renderer);
}

void Renderer::present() {
    SDL_RenderPresent(renderer);
}
