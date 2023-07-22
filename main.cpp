#include <iostream>
#include <SDL.h>
#include <ctime>
#include "src/Renderer.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int CELL_SIZE = 5;
const int GRID_WIDTH = WINDOW_WIDTH / CELL_SIZE;
const int GRID_HEIGHT = WINDOW_HEIGHT / CELL_SIZE;
const int FRAME_DELAY = 100;

class GameOfLife {
public:

    GameOfLife() : running(true), grid() {
        int startX = 1;
        int startY = 1;

        // Configurar el patrón inicial (Conway's Glider Gun) en la esquina superior izquierda
        grid[startX + 1][startY + 0] = true;
        grid[startX + 2][startY + 0] = true;
        grid[startX + 3][startY + 0] = true;
        grid[startX + 1][startY + 4] = true;
        grid[startX + 2][startY + 4] = true;
        grid[startX + 3][startY + 4] = true;
        grid[startX + 0][startY + 1] = true;
        grid[startX + 0][startY + 2] = true;
        grid[startX + 0][startY + 3] = true;
        grid[startX + 4][startY + 1] = true;
        grid[startX + 4][startY + 2] = true;
        grid[startX + 4][startY + 3] = true;

        // Configurar el patrón "Pulsar" en la esquina superior derecha
        startX = GRID_WIDTH - 15;
        startY = 1;

        grid[startX + 1][startY + 0] = true;
        grid[startX + 2][startY + 0] = true;
        grid[startX + 3][startY + 0] = true;
        grid[startX + 7][startY + 0] = true;
        grid[startX + 8][startY + 0] = true;
        grid[startX + 9][startY + 0] = true;
        grid[startX + 0][startY + 1] = true;
        grid[startX + 5][startY + 1] = true;
        grid[startX + 7][startY + 1] = true;
        grid[startX + 9][startY + 1] = true;
        grid[startX + 14][startY + 1] = true;
        grid[startX + 0][startY + 2] = true;
        grid[startX + 5][startY + 2] = true;
        grid[startX + 7][startY + 2] = true;
        grid[startX + 9][startY + 2] = true;
        grid[startX + 14][startY + 2] = true;
        grid[startX + 1][startY + 3] = true;
        grid[startX + 2][startY + 3] = true;
        grid[startX + 3][startY + 3] = true;
        grid[startX + 7][startY + 3] = true;
        grid[startX + 8][startY + 3] = true;
        grid[startX + 9][startY + 3] = true;

        // Configurar el patrón "Pulsar" en la esquina inferior izquierda
        startX = 1;
        startY = GRID_HEIGHT - 5;

        grid[startX + 1][startY + 0] = true;
        grid[startX + 2][startY + 0] = true;
        grid[startX + 3][startY + 0] = true;
        grid[startX + 1][startY + 4] = true;
        grid[startX + 2][startY + 4] = true;
        grid[startX + 3][startY + 4] = true;
        grid[startX + 0][startY + 1] = true;
        grid[startX + 0][startY + 2] = true;
        grid[startX + 0][startY + 3] = true;
        grid[startX + 4][startY + 1] = true;
        grid[startX + 4][startY + 2] = true;
        grid[startX + 4][startY + 3] = true;

        // Configurar el patrón "Pulsar" en la esquina inferior derecha
        startX = GRID_WIDTH - 5;
        startY = GRID_HEIGHT - 5;

        grid[startX + 1][startY + 0] = true;
        grid[startX + 2][startY + 0] = true;
        grid[startX + 3][startY + 0] = true;
        grid[startX + 1][startY + 4] = true;
        grid[startX + 2][startY + 4] = true;
        grid[startX + 3][startY + 4] = true;
        grid[startX + 0][startY + 1] = true;
        grid[startX + 0][startY + 2] = true;
        grid[startX + 0][startY + 3] = true;
        grid[startX + 4][startY + 1] = true;
        grid[startX + 4][startY + 2] = true;
        grid[startX + 4][startY + 3] = true;

        // Configurar el patrón "Pulsar" en el centro del tablero
        startX = GRID_WIDTH / 2 - 2;
        startY = GRID_HEIGHT / 2 - 2;

        grid[startX + 1][startY + 0] = true;
        grid[startX + 2][startY + 0] = true;
        grid[startX + 3][startY + 0] = true;
        grid[startX + 1][startY + 4] = true;
        grid[startX + 2][startY + 4] = true;
        grid[startX + 3][startY + 4] = true;
        grid[startX + 0][startY + 1] = true;
        grid[startX + 0][startY + 2] = true;
        grid[startX + 0][startY + 3] = true;
        grid[startX + 4][startY + 1] = true;
        grid[startX + 4][startY + 2] = true;
        grid[startX + 4][startY + 3] = true;

        std::srand(static_cast<unsigned>(std::time(0)));

        // Configurar el patrón inicial aleatorio
        for (int x = 0; x < GRID_WIDTH; ++x) {
            for (int y = 0; y < GRID_HEIGHT; ++y) {
                // Generar un número aleatorio entre 0 y 1
                int randomValue = std::rand() % 2;
                grid[x][y] = (randomValue == 1);
            }
        }

    }


    void run() {
        initializeSDL();

        SDL_Window* window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
        Renderer renderer(window);

        while (running) {
            handleEvents();

            if (running) {
                updateState();
                renderScene(renderer);
                SDL_Delay(FRAME_DELAY);
            }
        }

        SDL_DestroyWindow(window);
        SDL_Quit();
    }

private:
    bool running;
    bool grid[GRID_WIDTH][GRID_HEIGHT];

    void initializeSDL() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
            exit(1);
        }
    }

    void handleEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
            }
        }
    }

    void updateState() {
        bool newGrid[GRID_WIDTH][GRID_HEIGHT];

        for (int x = 0; x < GRID_WIDTH; ++x) {
            for (int y = 0; y < GRID_HEIGHT; ++y) {
                int liveNeighbors = countLiveNeighbors(x, y);

                if (grid[x][y]) {
                    // Cell is alive
                    if (liveNeighbors < 2 || liveNeighbors > 3) {
                        // Cell dies due to underpopulation or overpopulation
                        newGrid[x][y] = false;
                    } else {
                        // Cell survives
                        newGrid[x][y] = true;
                    }
                } else {
                    // Cell is dead
                    if (liveNeighbors == 3) {
                        // Cell becomes alive due to reproduction
                        newGrid[x][y] = true;
                    } else {
                        // Cell remains dead
                        newGrid[x][y] = false;
                    }
                }
            }
        }

        // Update the grid
        for (int x = 0; x < GRID_WIDTH; ++x) {
            for (int y = 0; y < GRID_HEIGHT; ++y) {
                grid[x][y] = newGrid[x][y];
            }
        }
    }

    int countLiveNeighbors(int x, int y) {
        int count = 0;

        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) {
                    continue;  // Skip the current cell
                }

                int nx = x + dx;
                int ny = y + dy;

                // Wrap around the grid edges
                if (nx < 0) {
                    nx = GRID_WIDTH - 1;
                } else if (nx >= GRID_WIDTH) {
                    nx = 0;
                }

                if (ny < 0) {
                    ny = GRID_HEIGHT - 1;
                } else if (ny >= GRID_HEIGHT) {
                    ny = 0;
                }

                if (grid[nx][ny]) {
                    ++count;
                }
            }
        }

        return count;
    }

    void renderScene(Renderer& renderer) {
        SDL_Renderer* sdlRenderer = renderer.getRenderer();
        SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
        SDL_RenderClear(sdlRenderer);

        SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);

        for (int x = 0; x < GRID_WIDTH; ++x) {
            for (int y = 0; y < GRID_HEIGHT; ++y) {
                if (grid[x][y]) {
                    int px = x * CELL_SIZE;
                    int py = y * CELL_SIZE;
                    point(sdlRenderer, px, py, CELL_SIZE);
                }
            }
        }

        renderer.present();
    }

    void point(SDL_Renderer* renderer, int x, int y, int size) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                SDL_RenderDrawPoint(renderer, x + i, y + j);
            }
        }
    }
};

int main(int argc, char* argv[]) {
    GameOfLife game;
    game.run();

    return 0;
}
