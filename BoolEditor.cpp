#include "BoolEditor.h"

BoolEditor::BoolEditor(
        const std::string& name,
        const bool value,
        std::function<void(const bool)> onValueChanged) :
    ValueEditor(name),
    _editing(false),
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
    return _editing;
}

void BoolEditor::Click()
{
    //_editing = !_editing;
    SetValue(!GetValue());
}

void BoolEditor::ChangeValue(const int delta)
{
    SetValue(!GetValue());
}

int BoolEditor::GetActualWidth() const
{
    if (_width < 0)
    {
        return ValueEditor::GetActualWidth() + ValueEditor::GetActualHeight();
    }
    return _width;
}

void BoolEditor::Render(Paint& paint, const int x, const int y) const
{
    const int boxWidth = GetActualWidth();
    const int boxHeight = GetActualHeight();

    // name
    std::string name = _utf8name + ":";
    int back, front;
    GetColors(IsSelected() && !IsEditing(), &back, &front);
    paint.DrawFilledRectangle(x, y, x + boxWidth, y + boxHeight, back);
    paint.DrawUtf8StringAt(x + _padding, y + _padding, name.c_str(), &_font, front, TextAlignment::LEFT);

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
    
    // border
    paint.DrawRectangle(x, y, x + boxWidth, y + boxHeight, BLACK);
}