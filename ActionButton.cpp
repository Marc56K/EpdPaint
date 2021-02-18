#include "ActionButton.h"

ActionButton::ActionButton(
        const std::string& name,
        std::function<void(void)> onClick) :
    PropertyPageEntry(name),
    _onClick(onClick)
{
}

ActionButton::~ActionButton()
{
}

bool ActionButton::IsEditing() const
{
    return false;
}

bool ActionButton::Click()
{
    _onClick();
    return IsEditing();
}

bool ActionButton::Scroll(const int delta)
{
    
    return IsEditing();
}

void ActionButton::Render(Paint& paint, const int x, const int y)
{
    const int boxWidth = GetActualWidth();
    const int boxHeight = GetActualHeight();

    // name
    int back, front;
    GetColors(IsSelected() && !IsEditing(), &back, &front);
    paint.DrawFilledRectangle(x, y, x + boxWidth, y + boxHeight, back);
    paint.DrawUtf8StringAt(x + boxWidth / 2, y + _padding, _utf8name.c_str(), &_font, front, TextAlignment::CENTER);

    // border
    paint.DrawRectangle(x, y, x + boxWidth, y + boxHeight, BLACK);
}