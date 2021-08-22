#include "BasicRenderer.h"

BasicRenderer::BasicRenderer(Framebuffer* TargetFrameBuffer, PSF1_FONT* PSF1_Font) {
    this->TargetFramebuffer = TargetFrameBuffer;
    this->PSF1_Font = PSF1_Font;
}

void BasicRenderer::PutChar(char chr, unsigned int xOff, unsigned int yOff) {
	unsigned int* pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
	char* fontPtr = (char*)PSF1_Font->glyphBuffer + (chr * PSF1_Font->psf1_Header->charsize);
	for (unsigned long y = yOff; y < yOff + 16; y++) {
		for (unsigned long x = xOff; x < xOff + 8; x++) {
			if ((*fontPtr & (0b10000000 >> (x - xOff))) > 0) {
				*(unsigned int*)(pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = Color;
			}
		}
		fontPtr++;
	}
}

void BasicRenderer::PutPixel(unsigned int x, unsigned int y) {
    unsigned int* pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
    *(unsigned int*)(pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = Color;
}

void BasicRenderer::PutPixel(unsigned int x, unsigned int y, unsigned int c) {
    unsigned int* pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
    *(unsigned int*)(pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = c;
}

void BasicRenderer::Fill(unsigned int color) {
    unsigned int* pixPtr = (unsigned int*)TargetFramebuffer->BaseAddress;
    for (int y = 0; y < TargetFramebuffer->Height; y++) {
        for (int x = 0; x < TargetFramebuffer->Width; x++) {
            *(unsigned int*)(pixPtr + x + (y * TargetFramebuffer->PixelsPerScanLine)) = color;
        }
    }
}

void BasicRenderer::DrawLine(int x0, int y0, int x1, int y1) {
    int dx, dy, p, x, y;
 
    dx = x1 - x0;
    dy = y1 - y0;
    
    x = x0;
    y = y0;
    
    p = 2 * dy - dx;
    
    while(x < x1) {
        if(p >= 0) {
            PutPixel(x, y);
            y = y + 1;
            p = p + 2 * dy -2 * dx;
        } else {
            PutPixel(x, y);
            p = p + 2 * dy;
        }
        x += 1;
    }
}

void BasicRenderer::Print(const char* str) {

	char* chr = (char*)str;
	while (*chr != 0) {
		PutChar(*chr, CursorPosition.X, CursorPosition.Y);
		CursorPosition.X += 8;
		if (CursorPosition.X + 8 > TargetFramebuffer->Width) {
			CursorPosition.X = 0;
			CursorPosition.Y += 16;
		}
		chr++;
	}
}