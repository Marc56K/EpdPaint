#include "TextPage.h"

TextPage::TextPage()
{
}

TextPage::~TextPage()
{
}

std::vector<std::string>& TextPage::Lines()
{
    return _lines;
}

void TextPage::Render(Paint& paint, const int x, const int y)
{
    const int boxHeight = GetActualHeight();
    for (size_t i = 0; i < _lines.size(); i++)
    {
        const int yPos = i * (_font.Height + 2) + y;
        if (yPos + _font.Height > y + boxHeight)
        {
            break;
        }

        paint.DrawUtf8StringAt(x, yPos + 1, _lines[i].c_str(), &_font, BLACK);
    }
}