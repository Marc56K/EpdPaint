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

void PageNavigator::SetCurrentPage(const int currentPageIdx)
{
    if (!_pages.empty())
    {
        const int idx = std::min<int>(_pages.size() - 1, std::max<int>(0, currentPageIdx));
        if (idx != _currentPageIdx)
        {
            auto& page = _pages[_currentPageIdx];
            if (page.control != nullptr && page.control->IsSelected())
            {
                page.control->Deselect();
            }
            _currentPageIdx = idx;
        }
    }
}

bool PageNavigator::Click()
{
    if (_currentPageIdx < _pages.size())
    {
        auto& page = _pages[_currentPageIdx];
        if (page.control != nullptr)
        {
            return page.control->Click();
        }
    }
    return false;
}

bool PageNavigator::Scroll(const int delta)
{
    if (_currentPageIdx < _pages.size())
    {
        auto& page = _pages[_currentPageIdx];
        if (page.control != nullptr && page.control->IsSelected())
        {
            return page.control->Scroll(delta);
        }
    }
    _currentPageIdx = std::min<int>(_pages.size() - 1, std::max<int>(0, _currentPageIdx + delta));
    return true;
}

void PageNavigator::Render(Paint& paint, const int x, const int y)
{
    if (!_pages.empty())
    {
        const int boxWidth = GetActualWidth() - 1;
        const int boxHeight = GetActualHeight();
        const auto& page = _pages[_currentPageIdx];

        int titleHeight = 0;
        if (!page.title.empty())
        {
            titleHeight = _font.Height + 1;

            paint.DrawFilledRectangle(x, y, x + boxWidth, y + _font.Height + 1, WHITE);
            paint.DrawRectangle(x, y, x + boxWidth, y + _font.Height + 1, BLACK);
            
            const int yPos = y + 1;
            paint.DrawUtf8StringAt(x + boxWidth / 2, yPos, page.title.c_str(), &_font, BLACK, TextAlignment::CENTER);

            if (_currentPageIdx > 0)
            {
                paint.DrawUtf8StringAt(x + 3, yPos, "<", &_font, BLACK, TextAlignment::LEFT);
            }

            if (_currentPageIdx + 1 < _pages.size())
            {
                paint.DrawUtf8StringAt(x + boxWidth - 1, yPos, ">", &_font, BLACK, TextAlignment::RIGHT);
            }
        }

        if (page.control != nullptr)
        {
            paint.DrawFilledRectangle(x, y + titleHeight, x + boxWidth, y + boxHeight, WHITE);
            paint.DrawRectangle(x, y + titleHeight, x + boxWidth, y + boxHeight, BLACK);

            page.control->SetWdith(boxWidth - 4);
            page.control->SetHeight(boxHeight - titleHeight - 3);
            page.control->Render(paint, x + 2, y + titleHeight + 2);
        }
    }
}