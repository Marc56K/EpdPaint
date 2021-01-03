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

std::string NumberEditor::GetValueAsString() const
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(_decimalPlaces) << GetValue() << _unit;
    return ss.str();
}

double NumberEditor::SetValue(const double value)
{
    double oldValue = _value;
    _value = std::max(_minValue, std::min(_maxValue, value));
    if (oldValue != _value && _onValueChanged != nullptr)
    {
        _onValueChanged(GetValue());
    }
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

int NumberEditor::GetActualWidth() const
{
    if (_width < 0)
    {
        return (_name.length() + GetValueAsString().length() + 3) * _font.Width + 2 * _padding;
    }
    return _width;
}

int NumberEditor::GetActualHeight() const
{
    if (_height < 0)
    {
        return _font.Height + 2 * _padding;
    }
    return _height;
}

void NumberEditor::Render(Paint& paint, const int x, const int y) const
{
    std::string name = GetName() + ":";
    std::string value = GetValueAsString();

    int colors[3] = { 1, 0, 0 }; // BG, Border, Text
    if (IsSelected())
    {
        colors[0] = 0; // BG black
        colors[2] = 1; // Text white        

        if (IsEditing())
        {
            value = "[" + value + "]";
        }
    }

    const int boxWidth = GetActualWidth();
    const int boxHeight = GetActualHeight();

    paint.DrawFilledRectangle(x, y, x + boxWidth, y + boxHeight, colors[0]);
    paint.DrawRectangle(x, y, x + boxWidth, y + boxHeight, colors[1]);

    paint.DrawUtf8StringAt(x + _padding, y + _padding, name.c_str(), &_font, colors[2], TextAlignment::LEFT);
    paint.DrawUtf8StringAt(x + boxWidth - _padding, y + _padding, value.c_str(), &_font, colors[2], TextAlignment::RIGHT);
}