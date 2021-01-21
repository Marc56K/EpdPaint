#include "OptionEditor.h"
#include <cmath>
#include <iomanip>
#include <sstream>

static const std::string emptyString = "";

OptionEditor::OptionEditor(
        const std::string& name,
        const std::vector<std::string>& options,
        const uint8_t selectedIdx,
        std::function<void(const uint8_t, const std::string&)> onValueChanged) : 
    ValueEditor(name),
    _options(options),
    _selectedIdx(selectedIdx),
    _onValueChanged(onValueChanged),
    _editing(false)
{
    SetSelectedIdx(selectedIdx);
}

OptionEditor::~OptionEditor()
{    
}

uint8_t OptionEditor::GetSelectedIdx() const
{
    return _selectedIdx;
}

void OptionEditor::SetSelectedIdx(const uint8_t selectedIdx)
{
    const uint8_t newIdx = _options.empty() ? 0 : std::max<uint8_t>(0, std::min<uint8_t>(_options.size() - 1, selectedIdx));
    if (_selectedIdx != newIdx)
    {
        _selectedIdx = newIdx;
        if (_onValueChanged != nullptr)
        {
            _onValueChanged(_selectedIdx, GetValue());
        }
    }
}

const std::string& OptionEditor::GetValue() const
{
    if (GetSelectedIdx() < _options.size())
    {
        return _options[GetSelectedIdx()];
    }
    return emptyString;
}

bool OptionEditor::IsEditing() const
{
    return _editing;
}

void OptionEditor::Click()
{
    _editing = !_editing;
}

void OptionEditor::Scroll(const int delta)
{
    int idx = delta + GetSelectedIdx();
    SetSelectedIdx(std::max(0, idx));
}

void OptionEditor::Render(Paint& paint, const int x, const int y)
{
    ValueEditor::Render(paint, x, y);
    
    const int boxWidth = GetActualWidth();
    const int boxHeight = GetActualHeight();

    int back, front;
    GetColors(IsSelected() && !IsEditing(), &back, &front);

    if (GetSelectedIdx() < _options.size())
    {
        const std::string& value = GetValue();

        const int xRight = x + boxWidth - _padding;
        const int xLeft = xRight - value.length() * _font.Width;
        if (IsEditing())
        {
            GetColors(true, &back, &front);
            paint.DrawFilledRectangle(xLeft, y, xRight, y + boxHeight, back);
        }
        paint.DrawUtf8StringAt(xRight, y + _padding, value.c_str(), &_font, front, TextAlignment::RIGHT);
    }
}