#include "PropertyPageEntry.h"
#include <sstream>

PropertyPageEntry::PropertyPageEntry(const std::string& utf8name) :
    _utf8name(utf8name),
    _latin1name(Paint::Utf8ToLatin1String(utf8name.c_str())),
    _padding(2)
{    
}

PropertyPageEntry::~PropertyPageEntry()
{    
}

const std::string& PropertyPageEntry::GetUtf8Name() const
{
    return _utf8name;
}

bool PropertyPageEntry::IsEditing() const
{
    return false;
}

void PropertyPageEntry::SetPadding(const int padding)
{
    _padding = padding;
}

int PropertyPageEntry::GetActualWidth() const
{
    if (_width <= 0)
    {
        return (_latin1name.length() + 10) * _font.Width + 2 * _padding;
    }
    return _width;
}

int PropertyPageEntry::GetActualHeight() const
{
    if (_height <= 0)
    {
        return _font.Height + 2 * _padding;
    }
    return _height;
}

void PropertyPageEntry::Render(Paint& paint, const int x, const int y)
{
    const int boxWidth = GetActualWidth();
    const int boxHeight = GetActualHeight();

    // name
    const std::string name = _utf8name + ":";
    int back, front;
    GetColors(IsSelected() && !IsEditing(), &back, &front);
    paint.DrawFilledRectangle(x, y, x + boxWidth, y + boxHeight, back);
    paint.DrawUtf8StringAt(x + _padding, y + _padding, name.c_str(), &_font, front, TextAlignment::LEFT);

    // border
    paint.DrawRectangle(x, y, x + boxWidth, y + boxHeight, BLACK);
}

void PropertyPageEntry::GetColors(const bool selected, int* back, int* front)
{
    auto setColor = [](int* target, const int color)
    {
        if (target != nullptr)
        {
            *target = color;
        }
    };

    if (selected)
    {
        setColor(back, BLACK);
        setColor(front, WHITE);
    }
    else
    {
        setColor(back, WHITE);
        setColor(front, BLACK);
    }
}