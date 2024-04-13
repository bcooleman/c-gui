#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <string.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Function to initialize SDL and create a window and renderer
bool init(SDL_Window **window, SDL_Renderer **renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    *window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        SDL_DestroyWindow(*window);
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Initialize SDL_ttf for text rendering
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
        return false;
    }

    return true;
}

// Main function
int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    if (!init(&window, &renderer)) {
        SDL_Quit();
        return 1;
    }

    bool quit = false;
    SDL_Event e;

    // Main loop
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            // Additional event handling here for text input
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
        SDL_RenderClear(renderer);

        // Draw text boxes as rectangles
        SDL_Rect textBox1 = {0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
        SDL_Rect textBox2 = {WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
        SDL_Rect textBox3 = {0, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
        SDL_Rect textBox4 = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
        SDL_RenderDrawRect(renderer, &textBox1);
        SDL_RenderDrawRect(renderer, &textBox2);
        SDL_RenderDrawRect(renderer, &textBox3);
        SDL_RenderDrawRect(renderer, &textBox4);

        // Update screen
        SDL_RenderPresent(renderer);
    }

    // Free resources and close SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
