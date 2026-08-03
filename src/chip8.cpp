#include "chip8.h"

Chip8::Chip8() {
    for (unsigned int i = 0; i < FONTSET_SIZE; i++) {
        memory[FONTSET_START_ADDRESS + i] = fonts[i];
    }
    pc = ROM_START_ADDRESS;
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
    std::streampos fileSize = inFile.tellg();
    std::cout << "File size: " << fileSize << " bytes." << std::endl;
    unsigned int valid_size = MEMORY_SIZE - ROM_START_ADDRESS;
    if (fileSize > valid_size) {
        std::cerr << "ROM File is too big!" << std::endl;
        return -1;
    }
    else
        std::cout << "File size is acceptable!" << std::endl;
    inFile.seekg(0, std::ios::beg);

    //Load ROM file into memory 
    inFile.read(reinterpret_cast<char*>(memory + ROM_START_ADDRESS), fileSize);

    return 1;
}

void Chip8::debug_dump(unsigned int start_pos, unsigned int length) const{
    if (start_pos >= MEMORY_SIZE) return;
    if (length > MEMORY_SIZE - start_pos) length = MEMORY_SIZE - start_pos;

    for (unsigned int i = 0; i < length; ++i) {
        if (i % 16 == 0) std::printf("0x%04X: ", start_pos + i);
        std::printf("%02x", memory[start_pos + i]);
        if (i % 2 == 1)  std::printf(" ");
        if (i % 16 == 15 || i == length - 1) std::printf("\n");
    }
}

uint16_t Chip8::fetch() {
    uint16_t opcode = (memory[pc] << 8) | memory[pc + 1];
    pc += 2;
    return opcode;
}

void Chip8::disassemble(uint16_t opcode) {
    uint8_t first_nibble = (opcode & 0xF000) >> 12;

}