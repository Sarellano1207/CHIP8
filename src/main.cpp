#include <SDL2/SDL.h>
#include <cstdio>
#include "chip8.h"

constexpr int CHIP8_WIDTH  = 64;
constexpr int CHIP8_HEIGHT = 32;
constexpr int SCALE = 15;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "No File Path Included! Please include a filepath to a ROM file :)\n";
        return 1;
    }

    std::string path = argv[1];
    //std::string path = "roms/1-chip8-logo.ch8";
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "Error: File does not exist or cannot be opened.\n";
        return 1;
    }

    // Testing
    Chip8 test;
    int result = test.loadROM(path);
    std::cout << "ROM Loaded result: " << result << std::endl;

    for (int i = 0; i < 8; i++) {
        std::printf("%04X ", test.fetch());
    }

    uint16_t test_opcode = 0x3C45;
    test.disassemble(test_opcode);


    // SDL Stuff
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "CHIP-8",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        CHIP8_WIDTH * SCALE, CHIP8_HEIGHT * SCALE,
        SDL_WINDOW_SHOWN);

    if (!window) {
        std::fprintf(stderr, "CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            if (event.type == SDL_KEYDOWN &&
                event.key.keysym.sym == SDLK_ESCAPE) running = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}