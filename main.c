#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>  // Include SDL2_gfx
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void handleEvents(SDL_Event e, bool* quit, SDL_Rect buttonRect, SDL_Rect requestAllButtonRect);
void renderText(SDL_Renderer* renderer, const char* text, int x, int y, SDL_Color color);

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL GUI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Rect buttonRect = {350, 270, 100, 50};
    SDL_Rect requestAllButtonRect = {350, 550, 100, 50};

    SDL_Color black = {0, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            handleEvents(event, &quit, buttonRect, requestAllButtonRect);
        }

        SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255); // Light grey background
        SDL_RenderClear(renderer);

        // Render GET request and payloads with basic text rendering
        renderText(renderer, "GET / HTTP/2.0\nHost: example.com", 20, 20, black);
        renderText(renderer, "XSS Payloads:\n\"><script>alert(1)</script>\n<script>console.log('xss')</script>\n<script src='http://malicious.com/x.js'></script>\nSQL Injections:\n' OR '1'='1\n' OR 1=1--\n'; DROP TABLE users;", 20, 320, black);

        // Render buttons with text
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue buttons
        SDL_RenderFillRect(renderer, &buttonRect);
        SDL_RenderFillRect(renderer, &requestAllButtonRect);
        renderText(renderer, "Request", 350 + 25, 270 + 15, white); // Center text manually
        renderText(renderer, "Request All", 350 + 10, 550 + 15, white); // Center text manually

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void handleEvents(SDL_Event e, bool* quit, SDL_Rect buttonRect, SDL_Rect requestAllButtonRect) {
    if (e.type == SDL_QUIT) {
        *quit = true;
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        if ((e.button.x >= buttonRect.x && e.button.x <= buttonRect.x + buttonRect.w) &&
            (e.button.y >= buttonRect.y && e.button.y <= buttonRect.y + buttonRect.h)) {
            printf("Clicked Request!\n");
        } else if ((e.button.x >= requestAllButtonRect.x && e.button.x <= requestAllButtonRect.x + requestAllButtonRect.w) &&
                   (e.button.y >= requestAllButtonRect.y && e.button.y <= requestAllButtonRect.y + requestAllButtonRect.h)) {
            printf("Clicked Request All!\n");
        }
    }
}

void renderText(SDL_Renderer* renderer, const char* text, int x, int y, SDL_Color color) {
    stringRGBA(renderer, x, y, text, color.r, color.g, color.b, color.a);
}
