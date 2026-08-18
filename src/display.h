#ifndef DISPLAY_H
#define DISPLAY_H

#include "raylib.h"
#include <cstdint>

class Display {
private:
    int width{};
    int height{};
    int scale{};
    uint8_t* display;

public:
    Display(int width, int height, int scale, uint8_t display[]);
};

#endif