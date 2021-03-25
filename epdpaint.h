#pragma once

// Display orientation
#define ROTATE_0            0
#define ROTATE_90           1
#define ROTATE_180          2
#define ROTATE_270          3

#define BLACK 0
#define WHITE 1

#include "fonts.h"
#include "images.h"
#include <string>

enum TextAlignment
{
    LEFT = 0,
    CENTER,
    RIGHT
};

enum BitsPerPixel
{
    ONE_BIT = 0,
    TWO_BITS,
    FOUR_BITS
};

class Paint 
{
public:
    Paint(unsigned char* image, int width, int height, BitsPerPixel bpp = ONE_BIT);
    ~Paint();
    void Clear(int colored);
    int  GetWidth(void);
    void SetWidth(int width);
    int  GetHeight(void);
    void SetHeight(int height);
    int  GetRotate(void);
    void SetRotate(int rotate);
    unsigned char* GetImage(void);
    void DrawAbsolutePixel(int x, int y, int colored);
    void DrawPixel(int x, int y, int colored);
    void DrawCharAt(int x, int y, char ascii_char, sFONT* font, int colored);
    void DrawStringAt(int x, int y, const char* text, sFONT* font, int colored);
    void DrawUtf8StringAt(int x, int y, const char* text, sFONT* font, int colored, TextAlignment alignment = TextAlignment::LEFT);
    void DrawLine(int x0, int y0, int x1, int y1, int colored);
    void DrawHorizontalLine(int x, int y, int width, int colored);
    void DrawVerticalLine(int x, int y, int height, int colored);
    void DrawRectangle(int x0, int y0, int x1, int y1, int colored);
    void DrawFilledRectangle(int x0, int y0, int x1, int y1, int colored);
    void DrawCircle(int x, int y, int radius, int colored);
    void DrawFilledCircle(int x, int y, int radius, int colored);
    void DrawImage(int x, int y, sIMAGE* img);

    static std::string Utf8ToLatin1String(const char* utf8Text);

private:
    unsigned char* image;
    int width;
    int height;
    int rotate;
    BitsPerPixel bpp;
};