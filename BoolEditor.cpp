#include "BoolEditor.h"

BoolEditor::BoolEditor(
        const std::string& name,
        const bool value,
        std::function<void(const bool)> onValueChanged) :
    PropertyPageEntry(name),
    _value(value),
    _onValueChanged(onValueChanged)
{
}

BoolEditor::~BoolEditor()
{
}

bool BoolEditor::GetValue() const
{
    return _value;
}

bool BoolEditor::SetValue(const bool value)
{
    if (_value != value)
    {
        _value = value;
        if (_onValueChanged != nullptr)
        {
            _onValueChanged(_value);
        }
    }
    return _value;
}

bool BoolEditor::IsEditing() const
{
    return false;
}

bool BoolEditor::Click()
{
    SetValue(!GetValue());
    return IsEditing();
}

bool BoolEditor::Scroll(const int delta)
{
    SetValue(!GetValue());
    return IsEditing();
}

void BoolEditor::Render(Paint& paint, const int x, const int y)
{
    PropertyPageEntry::Render(paint, x, y);
    
    const int boxWidth = GetActualWidth();
    const int boxHeight = GetActualHeight();

    int back, front;
    GetColors(IsSelected() && !IsEditing(), &back, &front);

    // value
    const int xRight = x + boxWidth - _padding;
    const int xLeft = xRight - boxHeight;
    if (IsEditing())
    {
        GetColors(true, &back, &front);
        paint.DrawFilledRectangle(xLeft, y, xRight, y + boxHeight, back);
    }

    const int radius = _font.Height / 2 - 2;
    const int xCenter = xRight - radius - _padding;
    const int yCenter = y + boxHeight / 2;

    paint.DrawCircle(xCenter, yCenter, radius, front);
    if (_value)
    {        
        paint.DrawFilledCircle(xCenter, yCenter, radius / 2, front);
    }
}