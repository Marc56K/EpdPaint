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
        return (_latin1name.length() + GetValueAsString().length() + 2) * _font.Width + 2 * _padding;
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
    std::string name = _utf8name + ":";
    std::string value = GetValueAsString();

    const int boxWidth = GetActualWidth();
    const int boxHeight = GetActualHeight();

    // name
    int back, front;
    GetColors(IsSelected() && !IsEditing(), &back, &front);
    paint.DrawFilledRectangle(x, y, x + boxWidth, y + boxHeight, back);
    paint.DrawUtf8StringAt(x + _padding, y + _padding, name.c_str(), &_font, front, TextAlignment::LEFT);

    // value
    GetColors(IsSelected() || IsEditing(), &back, &front);
    const int xRight = x + boxWidth - _padding;
    const int xLeft = xRight - value.length() * _font.Width - _padding;
    paint.DrawFilledRectangle(xLeft, y, x + boxWidth, y + boxHeight, back);
    paint.DrawUtf8StringAt(xRight, y + _padding, value.c_str(), &_font, front, TextAlignment::RIGHT);

    // border
    paint.DrawRectangle(x, y, x + boxWidth, y + boxHeight, BLACK);
}