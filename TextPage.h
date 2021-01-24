#pragma once
#include "BaseControl.h"
#include <vector>

class TextPage : public BaseControl
{
public:
    TextPage();
    virtual ~TextPage();

    std::vector<std::string>& Lines();
    
    virtual void Render(Paint& paint, const int x, const int y) override;

private:
    std::vector<std::string> _lines;
};