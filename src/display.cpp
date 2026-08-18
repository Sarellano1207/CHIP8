#include "display.h"

Display::Display(int width, int height, int scale, uint8_t display[]): 
    width(width), 
    height(height), 
    scale(scale), 
    display(display) 
    {}

Display::~Display() {
    CloseWindow();
}

void Display::init(const char* title) {
    SetTraceLogLevel(LOG_ERROR);                 
    InitWindow(width * scale, height * scale, title);
}

bool Display::should_close() {
    return WindowShouldClose();
}

void Display::render() {
    BeginDrawing();
    ClearBackground(BLACK);

    for (int i = 0; i < width * height; i++) {
        if (display[i] > 0) {
            int row = i / width;
            int col = i % width;
            DrawRectangle(col * scale, row * scale, scale, scale, WHITE);
        }
    }

    EndDrawing();
}




