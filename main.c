#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Function declarations
void handleEvents(SDL_Event e, bool* quit, SDL_Rect button, SDL_Rect requestAllButton);
void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Rect* rect);
void okPopup();

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("SDL GUI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* font = TTF_OpenFont("arial.ttf", 24); // Ensure you have this font or change to one you have

    SDL_Rect topLeftRect = {20, 20, 360, 280};
    SDL_Rect bottomLeftRect = {20, 320, 360, 260};
    SDL_Rect buttonRect = {400, 270, 100, 60};
    SDL_Rect requestAllButtonRect = {350, 550, 100, 40};

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            handleEvents(event, &quit, buttonRect, requestAllButtonRect);
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white background
        SDL_RenderClear(renderer);

        // Render text in the top left square
        renderText(renderer, font, "GET / HTTP/2.0", &topLeftRect);

        // Render selectable, scrollable text in the bottom left square
        renderText(renderer, font, "\"><script>alert(1)</script>", &bottomLeftRect);

        // Render buttons
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // blue buttons
        SDL_RenderFillRect(renderer, &buttonRect);
        SDL_RenderFillRect(renderer, &requestAllButtonRect);

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}

void handleEvents(SDL_Event e, bool* quit, SDL_Rect button, SDL_Rect requestAllButton) {
    switch (e.type) {
        case SDL_QUIT:
            *quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (e.button.x >= button.x && e.button.x <= (button.x + button.w) && 
                e.button.y >= button.y && e.button.y <= (button.y + button.h)) {
                okPopup();
            } else if (e.button.x >= requestAllButton.x && e.button.x <= (requestAllButton.x + requestAllButton.w) && 
                       e.button.y >= requestAllButton.y && e.button.y <= (requestAllButton.y + requestAllButton.h)) {
                okPopup();
            }
            break;
    }
}

void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Rect* rect) {
    SDL_Color black = {0, 0, 0};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, black);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void okPopup() {
    // This function would realistically need to create a new window or similar to show a popup
    printf("Clicked!\n");
}
