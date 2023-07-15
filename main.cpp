#include <iostream>
#include <SDL.h>
#include "src/Renderer.h"

const int WINDOW_WIDTH = 300;
const int WINDOW_HEIGHT = 300;
const int CELL_SIZE = 5;
const int GRID_WIDTH = WINDOW_WIDTH / CELL_SIZE;
const int GRID_HEIGHT = WINDOW_HEIGHT / CELL_SIZE;
const int FRAME_DELAY = 100;

class GameOfLife {
public:

    GameOfLife() : running(true), grid() {
        // Patrón inicial: Stable "dirty" puffer train
        int startX = 3;
        int startY = GRID_HEIGHT / 2;

        // Configurar el patrón inicial
        grid[startX][startY] = true;
        grid[startX + 1][startY] = true;
        grid[startX + 2][startY - 1] = true;
        grid[startX + 2][startY + 1] = true;
        grid[startX + 3][startY - 1] = true;
        grid[startX + 3][startY + 2] = true;
        grid[startX + 4][startY - 1] = true;
        grid[startX + 4][startY + 2] = true;
        grid[startX + 5][startY] = true;
        grid[startX + 6][startY] = true;
        grid[startX + 7][startY] = true;
        grid[startX + 8][startY] = true;
        grid[startX + 9][startY] = true;
        grid[startX + 10][startY - 1] = true;
        grid[startX + 10][startY + 1] = true;
        grid[startX + 11][startY - 1] = true;
        grid[startX + 11][startY + 1] = true;
        grid[startX + 12][startY] = true;
        grid[startX + 13][startY] = true;
        grid[startX + 14][startY] = true;
        grid[startX + 15][startY] = true;
        grid[startX + 16][startY] = true;
        grid[startX + 17][startY - 1] = true;
        grid[startX + 17][startY + 1] = true;
        grid[startX + 18][startY - 1] = true;
        grid[startX + 18][startY + 1] = true;
        grid[startX + 19][startY] = true;
        grid[startX + 20][startY] = true;
        grid[startX + 21][startY] = true;
        grid[startX + 22][startY] = true;
        grid[startX + 23][startY] = true;
        grid[startX + 24][startY - 1] = true;
        grid[startX + 24][startY + 1] = true;
        grid[startX + 25][startY - 1] = true;
        grid[startX + 25][startY + 1] = true;
        grid[startX + 26][startY] = true;
        grid[startX + 27][startY] = true;
        grid[startX + 28][startY] = true;
        grid[startX + 50][startY] = true;
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
        SDL_SetRenderDrawColor(sdlRenderer, 128, 0, 128, 255);
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
