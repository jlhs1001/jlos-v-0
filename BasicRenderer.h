#pragma once
#include "math.h"
#include "Framebuffer.h"
#include "simplefonts.h"
#include <stdint.h>

class BasicRenderer {
public:
    BasicRenderer(Framebuffer* TargetFrameBuffer, PSF1_FONT* PSF1_Font);
    Point CursorPosition = {0, 0};
    Framebuffer* TargetFramebuffer;
    PSF1_FONT* PSF1_Font;
    unsigned int Color = 0xffffffff;
    void Print(const char* str);
    void PutChar(char chr, unsigned int xOff, unsigned int yOff);
    void PutPixel(unsigned int x, unsigned int y);
    void PutPixel(unsigned int x, unsigned int y, unsigned int c);
    void DrawLine(int x0, int y0, int x1, int y1);
    void Fill(unsigned int color);
};