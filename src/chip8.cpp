#include <chip8.h>

Chip8::Chip8() {
    for (unsigned int i = 0; i < FONTSET_SIZE; i++) {
        memory[FONTSET_START_ADDRESS + i] = fonts[i];
    }
}

void Chip8::loadROM(const std::string& path) {
    std::ifstream inFile();
}