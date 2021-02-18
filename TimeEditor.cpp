#include "TimeEditor.h"
#include <iomanip>
#include <sstream>
#include "MathUtils.h"

TimeEditor::TimeEditor(
        const std::string& name,
        const uint8_t hh,
        const uint8_t mm,
        std::function<void(const uint8_t hh, const uint8_t mm)> onValueChanged) :
    PropertyPageEntry(name),
    _hh(hh),
    _mm(mm),
    _onValueChanged(onValueChanged),
    _editMode(0)
{    
    SetValue(hh, mm);
}

TimeEditor::~TimeEditor()
{    
}

void TimeEditor::GetValue(uint8_t& hh, uint8_t& mm) const
{
    hh = _hh;
    mm = _mm;
}

void TimeEditor::SetValue(const uint8_t hh, const uint8_t mm)
{
    if (_hh != hh || _mm != mm)
    {
        _hh = hh % 24;
        _mm = mm % 60;
        if (_onValueChanged != nullptr)
        {
            _onValueChanged(_hh, _mm);
        }
    }
}

bool TimeEditor::IsEditing() const
{
    return _editMode > 0;
}

bool TimeEditor::Click()
{
    _editMode = (_editMode + 1) % 3;
    return IsEditing();
}

bool TimeEditor::Scroll(const int delta)
{
    switch (_editMode)
    {
    case 1:
        SetValue(MathUtils::Modulo((int)_hh + delta, 24), _mm);
        break;
    case 2:
        SetValue(_hh, MathUtils::Modulo((int)_mm + delta, 60));
        break;
    default:
        break;
    }
    return IsEditing();
}

void TimeEditor::Render(Paint& paint, const int x, const int y)
{
    PropertyPageEntry::Render(paint, x, y);
    
    const int boxWidth = GetActualWidth();
    const int boxHeight = GetActualHeight();

    int back, front;
    GetColors(IsSelected() && !IsEditing(), &back, &front);

    // time
    paint.DrawUtf8StringAt(x + boxWidth - _padding, y + _padding, ":  ", &_font, front, TextAlignment::RIGHT);
    for (uint8_t i = 0; i < 2; ++i)
    {
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << (int)(i == 0 ? _hh : _mm);
        std::string value = ss.str();
        
        const int xLeft = x + boxWidth - _padding - 5 * _font.Width + (i * 2 + i) * _font.Width;
        const int xRight = xLeft + 2 * _font.Width;
        
        if (i + 1 == _editMode)
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
}