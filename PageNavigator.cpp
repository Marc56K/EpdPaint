#include "PageNavigator.h"
#include "MathUtils.h"

PageNavigator::PageNavigator()
    : _font(Font12), _currentPageIdx(0)
{
}

PageNavigator::~PageNavigator()
{
}

void PageNavigator::SetFont(sFONT& font)
{
    _font = font;
}

void PageNavigator::AddPage(const std::string& title, std::shared_ptr<BaseControl> control)
{
    _pages.push_back({title, control});
}

void PageNavigator::Click()
{
    if (_currentPageIdx < _pages.size())
    {
        auto& page = _pages[_currentPageIdx];
        page.control->Click();
    }
}

void PageNavigator::Scroll(const int delta)
{
    if (_currentPageIdx < _pages.size())
    {
        auto& page = _pages[_currentPageIdx];
        if (page.control->IsSelected())
        {
            page.control->Scroll(delta);
            return;
        }
    }
    _currentPageIdx = MathUtils::Modulo<int>(_currentPageIdx + delta, _pages.size());
}

void PageNavigator::Render(Paint& paint, const int x, const int y)
{
    if (!_pages.empty())
    {
        const int boxWidth = GetActualWidth();
        const int boxHeight = GetActualHeight();

        paint.DrawFilledRectangle(x, y, x + boxWidth, y + boxHeight, WHITE);
        paint.DrawRectangle(x, y, x + boxWidth, y + boxHeight, BLACK);

        auto& page = _pages[_currentPageIdx];
        paint.DrawUtf8StringAt(x + boxWidth / 2, y + 1, page.title.c_str(), &_font, BLACK, TextAlignment::CENTER);

        paint.DrawHorizontalLine(x, y + _font.Height + 1, boxWidth, BLACK);

        page.control->SetWdith(boxWidth - 4);
        page.control->SetHeight(boxHeight - _font.Height - 3);
        page.control->Render(paint, x + 2, y + _font.Height + 3);
    }
}