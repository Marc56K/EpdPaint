#include "ValueEditor.h"
#include <sstream>

ValueEditor::ValueEditor(const std::string& utf8name) :
    _utf8name(utf8name),
    _latin1name(Paint::Utf8ToLatin1String(utf8name.c_str())),
    _padding(2)
{    
}

ValueEditor::~ValueEditor()
{    
}

const std::string& ValueEditor::GetUtf8Name() const
{
    return _utf8name;
}

bool ValueEditor::IsEditing() const
{
    return false;
}

void ValueEditor::SetPadding(const int padding)
{
    _padding = padding;
}

int ValueEditor::GetActualWidth() const
{
    if (_width <= 0)
    {
        return (_latin1name.length() + 10) * _font.Width + 2 * _padding;
    }
    return _width;
}

int ValueEditor::GetActualHeight() const
{
    if (_height <= 0)
    {
        return _font.Height + 2 * _padding;
    }
    return _height;
}

void ValueEditor::Render(Paint& paint, const int x, const int y)
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

void ValueEditor::GetColors(const bool selected, int* back, int* front)
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