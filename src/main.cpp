#include <cstdio>
#include "chip8.h"
#include "raylib.h"
#include "display.h"

constexpr int CHIP8_WIDTH  = 64;
constexpr int CHIP8_HEIGHT = 32;
constexpr int SCALE = 15;

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

    while (!screen.should_close()) {
        test.cycle();   
        screen.render();
    }
   
        

    return 0;
}