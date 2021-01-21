#pragma once
#include "BaseControl.h"
#include <string>
#include <vector>
#include <memory>

class PageNavigator : public BaseControl
{
private:
    struct PageInfo
    {
        std::string title;
        std::shared_ptr<BaseControl> control;
    };

public:
    PageNavigator();
    virtual ~PageNavigator();

    void SetFont(sFONT& font);

    void AddPage(const std::string& title, std::shared_ptr<BaseControl> control);

    virtual void Click() override;
    virtual void Scroll(const int delta) override;

    virtual void Render(Paint& paint, const int x, const int y) override;

private:
    sFONT& _font;
    int _currentPageIdx;
    std::vector<PageInfo> _pages;    
};