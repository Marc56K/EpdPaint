#include "StringEditor.h"
#include "MathUtils.h"

StringEditor::StringEditor(
        const std::string& name,
        const std::string& value,
        std::function<void(const std::string&)> onValueChanged) :
    ValueEditor(name),
    _editIdx(-1),
    _editChar(false),
    _value(value),
    _onValueChanged(onValueChanged)
{
}

StringEditor::~StringEditor()
{
}

const std::string& StringEditor::GetValue() const
{
    return _value;
}

void StringEditor::SetValue(const std::string& value)
{
    if (_value != value)
    {
        _value = value;
        if (_onValueChanged != nullptr)
        {
            _onValueChanged(_value);
        }
    }
}

bool StringEditor::IsEditing() const
{
    return _editIdx > -1;
}

void StringEditor::Click()
{
    if (_editIdx < 0)
    {
        _editIdx = 0;
        _editChar = false;
    }
    else
    {
        _editChar = !_editChar;
    }
}

void StringEditor::Scroll(const int delta)
{
    if (_editIdx > -1)
    {
        if (_editChar)
        {
            std::string value = _value;
            const char nac = ' ' - 1;
            const char minc = (value.length() > 1 && _editIdx < value.length() - 1) ? ' ' : nac;
            const char maxc = '~';
            int c = minc;
            if (_editIdx < value.length())
            {
                c = value[_editIdx];
            }

            const int val = delta + c - minc;
            c = (char)(MathUtils::Modulo(val, maxc - minc) + minc);
            if (_editIdx < value.length())
            {
                if (c == nac)
                {
                    value.resize(value.length() - 1);
                }
                else
                {
                    value[_editIdx] = c;
                }
            }
            else if (c != nac)
            {
                value += (char)c;
            }
            SetValue(value);
        }
        else
        {
            _editIdx = std::max(-1, std::min(_editIdx + delta, (int)_value.length()));
            if (_editIdx < 0)
            {
                _editChar = false;
            }
        }
    }
}

void StringEditor::Render(Paint& paint, const int x, const int y)
{
    ValueEditor::Render(paint, x, y);
    
    const int boxWidth = GetActualWidth();
    const int boxHeight = GetActualHeight();

    int back, front;
    GetColors(IsSelected() && !IsEditing(), &back, &front);

    std::string value = Paint::Utf8ToLatin1String(_value.c_str());
    if (IsEditing())
    {
        value += (char)0;
    }

    if (value.length() == 0)
    {
        return;
    }

    int maxChars = std::max<int>(_font.Width, boxWidth - _font.Width * (_latin1name.length() + 2)) / _font.Width;
    int editIdx = _editIdx;
    int xPos = x + boxWidth - _padding;
    int yPos = y + _padding;
    int startIdx = 0;
    int endIdx = ((int)value.length() - 1);    

    if (maxChars < value.length())
    {
        while (editIdx > startIdx + maxChars - 1)
        {
            ++startIdx;
        }
        endIdx = startIdx + maxChars - 1;
    }

    auto drawChar = [&](const int x, const int i, const int color)
    {
        if (value[i] != 0)
        {
            paint.DrawCharAt(x, yPos, value[i], &_font, color);
        }
        else
        {
            paint.DrawHorizontalLine(x + _font.Width / 2 - 2, yPos + _font.Height / 3, 5, color);
            paint.DrawVerticalLine(x + _font.Width / 2 + 3, yPos + _font.Height / 3, 3, color);
        }
    };

    for (int i = endIdx; i >= startIdx; --i)
    {
        xPos -= _font.Width;
        drawChar(xPos, i, front);

        if (i == editIdx)
        {
            if (_editChar)
            {
                paint.DrawFilledRectangle(xPos, y, xPos + _font.Width, y + boxHeight, front);
                drawChar(xPos, i, back);
            }
            else
            {
                paint.DrawRectangle(xPos, y, xPos + _font.Width, y + boxHeight, front);
            }
        }
    }
}