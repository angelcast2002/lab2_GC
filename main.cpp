#include <iostream>
#include <fstream>
#include <SDL.h>
#include "src/framebuffer.h"

void render() {
    Framebuffer framebuffer(800, 600);
    Color clearColor(0x00, 0x00, 0x00);

    framebuffer.clear(clearColor);

    // Poligono 1
    Color fillColor(0xFF, 0xFF, 0x00);       // Color de relleno (amarillo)
    Color borderColor(0xFF, 0xFF, 0xFF);     // Color de contorno (verde)
    std::vector<Vertex> poligono1{
            {165.0, 380.0},
            {185.0, 360.0},
            {180.0, 330.0},
            {207.0, 345.0},
            {233.0, 330.0},
            {230.0, 360.0},
            {250.0, 380.0},
            {220.0, 385.0},
            {205.0, 410.0},
            {193.0, 383.0}
    };

    // Poligono 2

    Color fillColor2(0, 0, 255);       // Relleno azul
    Color borderColor2(255, 255, 255); // Borde blanco
    std::vector<Vertex> vertices{
            {321.0, 335.0},
            {288.0, 286.0},
            {339.0, 251.0},
            {374.0, 302.0}
    };

    // Poligono 3
    Color fillColor3(255, 0, 0);         // Relleno rojo
    Color borderColor3(255, 255, 255);  // Borde blanco
    std::vector<Vertex> poligono3{
            {377.0, 249.0},
            {411.0, 197.0},
            {436.0, 249.0}
    };

    // Poligono 4
    Color fillColor4(0, 255, 0);         // Relleno verde
    Color borderColor4(255, 255, 255);  // Borde blanco
    std::vector<Vertex> poligono4{
            {413.0, 177.0},
            {448.0, 159.0},
            {502.0, 88.0},
            {553.0, 53.0},
            {535.0, 36.0},
            {676.0, 37.0},
            {660.0, 52.0},
            {750.0, 145.0},
            {761.0, 179.0},
            {672.0, 192.0},
            {659.0, 214.0},
            {615.0, 214.0},
            {632.0, 230.0},
            {580.0, 230.0},
            {597.0, 215.0},
            {552.0, 214.0},
            {517.0, 144.0},
            {466.0, 180.0}
    };

    // Poligono 5
    Color borderColor5(255, 255, 255);  // Borde blanco
    std::vector<Vertex> poligono5{
            {682.0, 175.0},
            {708.0, 120.0},
            {735.0, 148.0},
            {739.0, 170.0}
    };

    framebuffer.drawPolygon(poligono1, fillColor, borderColor);
    framebuffer.drawPolygon(vertices, fillColor2, borderColor2);
    framebuffer.drawPolygon(poligono3, fillColor3, borderColor3);
    framebuffer.drawPolygon(poligono4, fillColor4, borderColor4);
    framebuffer.drawPolygon(poligono5, clearColor, borderColor5);

    framebuffer.renderBuffer();
}

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("life", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED
    );

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Call our render function
        render(renderer);

        // Present the frame buffer to the screen
        SDL_RenderPresent(renderer);

        // Delay to limit the frame rate
        SDL_Delay(1000 / 60);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
