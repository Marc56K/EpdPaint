#include "NumberEditor.h"
#include <cmath>
#include <iomanip>
#include <sstream>

NumberEditor::NumberEditor(
        const std::string& name,
        const int decimalPlaces,
        const double stepSize,
        const double minValue, 
        const double maxValue, 
        const double value) : 
    ValueEditor(name),
    _decimalPlaces(decimalPlaces),
    _stepSize(stepSize),
    _minValue(minValue),
    _maxValue(maxValue),
    _editing(false)
{
    SetValue(value);
}

NumberEditor::~NumberEditor()
{    
}

double NumberEditor::GetValue() const
{
    return _value;
}

double NumberEditor::SetValue(const double value)
{
    _value = std::max(_minValue, std::min(_maxValue, value));
    return GetValue();
}

bool NumberEditor::IsEditing() const
{
    return _editing;
}

void NumberEditor::Click()
{
    _editing = !_editing;
}

void NumberEditor::ChangeValue(const int delta)
{
    SetValue(GetValue() + _stepSize * delta);
}

void NumberEditor::Render(Paint& paint, const int x, const int y, sFONT& font) const
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(_decimalPlaces) << GetValue();
    std::string valueString = ss.str();

    int colors[3] = { 1, 0, 0 }; // BG, Border, Text
    if (IsSelected())
    {
        colors[0] = 0; // BG black
        colors[2] = 1; // Text white        

        if (IsEditing())
        {
            valueString = "[" + valueString + "]";
        }
    }

    std::string txt = _name + ": " + valueString;

    const int boxWidth = txt.length() * font.Width;
    const int boxHeight = font.Height;

    paint.DrawFilledRectangle(x, y, x + boxWidth, y + boxHeight, colors[0]);
    paint.DrawRectangle      (x, y, x + boxWidth, y + boxHeight, colors[1]);
    paint.DrawUtf8StringAt   (x, y + 1, txt.c_str(), &font, colors[2]);
}