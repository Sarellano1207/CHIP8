#include <SDL2/SDL.h>
#include <cstdio>
#include "chip8.h"
#include "raylib.h"

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
    int load_rom_result = test.loadROM(path);
    std::cout << "ROM Loaded result: " << load_rom_result << std::endl;

    // Debug Dump first
    test.debug_dump(0x200, load_rom_result);

    // Test disassemble
    for (int i = 0; i < load_rom_result / 2; i++) {
        uint16_t pc_before_fetch = test.get_pc();
        uint16_t opcode = test.fetch();
        test.disassemble(opcode, pc_before_fetch);
    }   

    std::cout << "\n\nPrinting Over Range\n\n";
    
    test.disassemble_range(0x200, 0x200 + load_rom_result);

    for (unsigned int i = 0; i < CHIP8_WIDTH * CHIP8_HEIGHT; i++) {
        if (i % 2 == 0)
            test.display[i] = 1;
    }
    // Raylib Stuff
    InitWindow(CHIP8_WIDTH * SCALE, CHIP8_HEIGHT * SCALE, "Raylib Example");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            for (unsigned int i = 0; i < CHIP8_WIDTH * CHIP8_HEIGHT; i++) {                
                if (test.display[i] > 0) {
                    unsigned int row = i / CHIP8_WIDTH;
                    unsigned int col = i % CHIP8_WIDTH;
                    DrawRectangle(col * SCALE, row * SCALE, SCALE, SCALE, WHITE);     
                }
            }
        EndDrawing();
    }
    

    CloseWindow();
    return 0;
}