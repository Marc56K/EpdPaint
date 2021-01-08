#include "NumberEditor.h"
#include <cmath>
#include <iomanip>
#include <sstream>

NumberEditor::NumberEditor(
        const std::string& name,
        const std::string& unit,
        const int decimalPlaces,
        const double stepSize,
        const double minValue, 
        const double maxValue, 
        const double value,
        std::function<void(const double)> onValueChanged) : 
    ValueEditor(name),
    _unit(unit),
    _decimalPlaces(decimalPlaces),
    _stepSize(stepSize),
    _minValue(minValue),
    _maxValue(maxValue),
    _editing(false),
    _value(value),
    _onValueChanged(onValueChanged)
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

void NumberEditor::SetValue(const double value)
{
    const double newValue = std::max(_minValue, std::min(_maxValue, value));
    if (_value != newValue)
    {
        _value = newValue;
        if (_onValueChanged != nullptr)
        {
            _onValueChanged(_value);
        }
    }
}

bool NumberEditor::IsEditing() const
{
    return _editing;
}

void NumberEditor::Click()
{
    _editing = !_editing;
}

void NumberEditor::Scroll(const int delta)
{
    SetValue(GetValue() + _stepSize * delta);
}

void NumberEditor::Render(Paint& paint, const int x, const int y) const
{
    ValueEditor::Render(paint, x, y);
    
    const int boxWidth = GetActualWidth();
    const int boxHeight = GetActualHeight();

    int back, front;
    GetColors(IsSelected() && !IsEditing(), &back, &front);

    // unit
    int xRight = x + boxWidth - _padding;
    paint.DrawUtf8StringAt(xRight, y + _padding, _unit.c_str(), &_font, front, TextAlignment::RIGHT);

    // value
    std::stringstream ss;
    ss << std::fixed << std::setprecision(_decimalPlaces) << GetValue();
    std::string value =  ss.str();

    xRight -= _unit.length() * _font.Width;
    const int xLeft = xRight - value.length() * _font.Width;
    if (IsEditing())
    {
        GetColors(true, &back, &front);
        paint.DrawFilledRectangle(xLeft, y, xRight, y + boxHeight, back);
    }
    paint.DrawUtf8StringAt(xRight, y + _padding, value.c_str(), &_font, front, TextAlignment::RIGHT);
}