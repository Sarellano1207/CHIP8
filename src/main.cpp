#include <iostream>
#include <string>
#include <vector>
#include "chip8.h"
#include "display.h"
#include "raylib.h"

constexpr int CHIP8_WIDTH  = 64;
constexpr int CHIP8_HEIGHT = 32;
constexpr int SCALE = 15;
constexpr int CYCLES_PER_FRAME = 11; // ~600 instructions/sec at 60 FPS

// CHIP-8 keypad      Keyboard
// 1 2 3 C            1 2 3 4
// 4 5 6 D     ->     Q W E R
// 7 8 9 E            A S D F
// A 0 B F            Z X C V
// The key vars are defined in raylib already so we're just gonna use that
constexpr int KEYMAP[16] = {
    KEY_X,                          // 0
    KEY_ONE, KEY_TWO, KEY_THREE,    // 1 2 3
    KEY_Q, KEY_W, KEY_E,            // 4 5 6
    KEY_A, KEY_S, KEY_D,            // 7 8 9
    KEY_Z, KEY_C,                   // A B
    KEY_FOUR, KEY_R, KEY_F, KEY_V   // C D E F
};

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "No File Path Included! Please include a filepath to a ROM file :)\n";
        return 1;
    }
    
    // Get the path from cli
    std::string path = argv[1];

    // Testing
    Chip8 test;
    int load_rom_result = test.loadROM(path);
    std::cout << "ROM Loaded result: " << load_rom_result << std::endl;

    // Debug Dump first
    //test.debug_dump(0x200, load_rom_result);

    // Test disassemble
    /*
    for (int i = 0; i < load_rom_result / 2; i++) {
        uint16_t pc_before_fetch = test.get_pc();
        uint16_t opcode = test.fetch();
        test.disassemble(opcode, pc_before_fetch);
    }   
    */

    std::cout << "\n\nPrinting Over Range\n\n";
    
    // Test disassemble over a certain range
    // Currently, the output from the test disassmle from above should produce the same output
    /*
    test.disassemble_range(0x200, 0x200 + load_rom_result);

    for (unsigned int i = 0; i < CHIP8_WIDTH * CHIP8_HEIGHT; i++) {
        if (i % 2 == 0)
            test.display[i] = 1;
    }
    */
    // Raylib Stuff

    Display screen(CHIP8_WIDTH, CHIP8_HEIGHT, SCALE, test.display);
    screen.init("CHIP-8");
    SetTargetFPS(60);

    while (!screen.should_close()) {
        // Input
        for (int k = 0; k < 16; k++)
            test.set_key(k, IsKeyDown(KEYMAP[k]));

        // CPU
        for (int i = 0; i < CYCLES_PER_FRAME; i++)
            test.cycle();   

        // Timers tick at 60Hz, same as the frame rate
        test.update_timers();

        screen.render();
    }

    return 0;
}