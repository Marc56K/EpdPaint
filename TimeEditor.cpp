#include "TimeEditor.h"
#include <iomanip>
#include <sstream>
#include "MathUtils.h"

TimeEditor::TimeEditor(
        const std::string& name,
        const uint8_t hh,
        const uint8_t mm,
        std::function<void(const uint8_t hh, const uint8_t mm)> onTimeChanged) :
    ValueEditor(name),
    _hh(hh),
    _mm(mm),
    _onTimeChanged(onTimeChanged),
    _editingIdx(0)
{    
    SetTime(hh, mm);
}

TimeEditor::~TimeEditor()
{    
}

void TimeEditor::GetTime(uint8_t& hh, uint8_t& mm) const
{
    hh = _hh;
    mm = _mm;
}

std::string TimeEditor::GetTimeComponentAsString(const uint8_t timeComponent) const
{
    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << (int)timeComponent;
    return ss.str();
}

void TimeEditor::SetTime(const uint8_t hh, const uint8_t mm)
{
    if (_hh != hh || _mm != mm)
    {
        _hh = hh % 24;
        _mm = mm % 60;
        if (_onTimeChanged != nullptr)
        {
            _onTimeChanged(_hh, _mm);
        }
    }
}

bool TimeEditor::IsEditing() const
{
    return _editingIdx > 0;
}

void TimeEditor::Click()
{
    _editingIdx = (_editingIdx + 1) % 3;
}

void TimeEditor::ChangeValue(const int delta)
{
    switch (_editingIdx)
    {
    case 1:
        SetTime(MathUtils::Modulo((int)_hh + delta, 24), _mm);
        break;
    case 2:
        SetTime(_hh, MathUtils::Modulo((int)_mm + delta, 60));
        break;
    default:
        break;
    }
}

int TimeEditor::GetActualWidth() const
{
    if (_width < 0)
    {
        return ValueEditor::GetActualWidth() + 5 * _font.Width;
    }
    return _width;
}

void TimeEditor::Render(Paint& paint, const int x, const int y) const
{
    const int boxWidth = GetActualWidth();
    const int boxHeight = GetActualHeight();

    // name
    const std::string name = _utf8name + ":";
    int back, front;
    GetColors(IsSelected() && !IsEditing(), &back, &front);
    paint.DrawFilledRectangle(x, y, x + boxWidth, y + boxHeight, back);
    paint.DrawUtf8StringAt(x + _padding, y + _padding, name.c_str(), &_font, front, TextAlignment::LEFT);

    // time
    paint.DrawUtf8StringAt(x + boxWidth - _padding, y + _padding, ":  ", &_font, front, TextAlignment::RIGHT);
    for (uint8_t i = 0; i < 2; ++i)
    {
        std::string value = GetTimeComponentAsString(i == 0 ? _hh : _mm);
        
        const int xLeft = x + boxWidth - _padding - 5 * _font.Width + (i * 2 + i) * _font.Width;
        const int xRight = xLeft + 2 * _font.Width;
        
        if (i + 1 == _editingIdx)
        {
            GetColors(true, &back, &front);
            paint.DrawFilledRectangle(xLeft, y, xRight, y + boxHeight, back);
        }
        else
        {
            GetColors(IsSelected() && !IsEditing(), &back, &front);
        }

        paint.DrawUtf8StringAt(xLeft, y + _padding, value.c_str(), &_font, front, TextAlignment::LEFT);
    }

    // border
    paint.DrawRectangle(x, y, x + boxWidth, y + boxHeight, BLACK);
}