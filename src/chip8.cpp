#include "chip8.h"

Chip8::Chip8() {
    for (unsigned int i = 0; i < FONTSET_SIZE; i++) {
        memory[FONTSET_START_ADDRESS + i] = fonts[i];
    }
    pc = 0x200;
}

int Chip8::loadROM(const std::string& path) {
    // Open the file in the given path
    std::ifstream inFile(path, std::ios::binary | std::ios::ate);
    
    // Check if there was an error with the file
    if (!inFile) {
        std::cerr << "Error: file not found or can't open file!" << std::endl;
        return -1;
    }

    //If the file is open, check the size and either pass/fail it
    std::streampos fileSize;
    uint16_t valid_size;
    if (inFile.is_open()) {
        fileSize = inFile.tellg();
        std::cout << "File size: " << fileSize << " bytes." << std::endl;
        valid_size = 0x1000 - 0x200;
        if (fileSize > valid_size) {
            std::cout << "ROM File is too big!" << std::endl;
        }
        else
            std::cout << "File size is acceptable!" << std::endl;
        inFile.seekg(0, std::ios::beg);
    }

    //Load ROM file into memory 
    inFile.read(reinterpret_cast<char*>(memory + 0x200), fileSize);

    return 1;
}

void Chip8::debug_dump(unsigned int start_pos, unsigned int length) {
    if (start_pos >= MEMORY_SIZE) return;
    if (length > MEMORY_SIZE - start_pos) length = MEMORY_SIZE - start_pos;

    for (unsigned int i = 0; i < length; ++i) {
        if (i % 16 == 0) std::printf("0x%04X: ", start_pos + i);
        std::printf("%02x", memory[start_pos + i]);
        if (i % 2 == 1)  std::printf(" ");
        if (i % 16 == 15 || i == length - 1) std::printf("\n");
    }
}