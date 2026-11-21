#include <switch.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>

#define SCREEN_W 1280
#define SCREEN_H 720

static void draw_text(SDL_Renderer *renderer, TTF_Font *font,
                      const char *text, int x, int y, SDL_Color color) {
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, color);
    if (!surface) return;
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture) {
        SDL_Rect dst = { x, y, surface->w, surface->h };
        SDL_RenderCopy(renderer, texture, NULL, &dst);
        SDL_DestroyTexture(texture);
    }
    SDL_FreeSurface(surface);
}

int main(int argc, char **argv) {
    (void)argc; (void)argv;
    romfsInit();

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0) {
        romfsExit();
        return 1;
    }
    IMG_Init(IMG_INIT_PNG);
    if (TTF_Init() != 0) {
        IMG_Quit(); SDL_Quit(); romfsExit();
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "NXShigma", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN
    );
    SDL_Renderer *renderer = window
        ? SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
        : NULL;

    SDL_Texture *background = IMG_LoadTexture(renderer, "romfs:/nxshigma.png");

    /* A font is loaded from romfs. Add a TTF file to assets/fonts and update
       this path if you want custom typography. */
    TTF_Font *font = TTF_OpenFont("romfs:/font.ttf", 30);
    if (!font) font = TTF_OpenFont("romfs:/assets/font.ttf", 30);

    const char *items[] = {
        "About NXShigma",
        "System information",
        "Credits"
    };
    int selected = 0;
    bool running = (window && renderer);

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            if (event.type == SDL_CONTROLLERBUTTONDOWN) {
                if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_UP)
                    selected = (selected + 2) % 3;
                if (event.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_DOWN)
                    selected = (selected + 1) % 3;
                if (event.cbutton.button == SDL_CONTROLLER_BUTTON_B)
                    running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_UP) selected = (selected + 2) % 3;
                if (event.key.keysym.sym == SDLK_DOWN) selected = (selected + 1) % 3;
                if (event.key.keysym.sym == SDLK_ESCAPE) running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 10, 5, 20, 255);
        SDL_RenderClear(renderer);
        if (background) {
            SDL_RenderCopy(renderer, background, NULL, NULL);
        } else {
            SDL_SetRenderDrawColor(renderer, 35, 8, 65, 255);
            SDL_RenderClear(renderer);
        }

        /* Dark translucent panel behind the menu. */
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 185);
        SDL_Rect panel = { 70, 70, 560, 570 };
        SDL_RenderFillRect(renderer, &panel);

        SDL_Color white = {245, 240, 255, 255};
        SDL_Color purple = {190, 90, 255, 255};
        if (font) {
            draw_text(renderer, font, "NXSHIGMA", 110, 105, purple);
            draw_text(renderer, font, "HOMEbrew", 112, 155, white);
            for (int i = 0; i < 3; i++) {
                SDL_Rect bar = { 105, 260 + i * 90, 480, 62 };
                SDL_SetRenderDrawColor(renderer,
                    i == selected ? 115 : 35,
                    i == selected ? 35 : 20,
                    i == selected ? 170 : 55, 225);
                SDL_RenderFillRect(renderer, &bar);
                draw_text(renderer, font, items[i], 130, 275 + i * 90, white);
            }
            draw_text(renderer, font, "D-PAD: MOVE   B: EXIT", 110, 565, white);
        } else {
            /* Still provides a visible menu if no font has been added. */
            for (int i = 0; i < 3; i++) {
                SDL_Rect bar = { 105, 250 + i * 100, 480, 70 };
                SDL_SetRenderDrawColor(renderer,
                    i == selected ? 150 : 45, 35, i == selected ? 220 : 75, 230);
                SDL_RenderFillRect(renderer, &bar);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    if (font) TTF_CloseFont(font);
    if (background) SDL_DestroyTexture(background);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    romfsExit();
    return 0;
}
