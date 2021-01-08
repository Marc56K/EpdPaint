#pragma once
#include <memory>
#include <vector>
#include "NumberEditor.h"
#include "TimeEditor.h"
#include "BoolEditor.h"
#include "StringEditor.h"
#include "OptionEditor.h"

class PropertyPage
{
public:
    PropertyPage(sFONT& font);

    void Add(std::shared_ptr<ValueEditor> editor);

    std::shared_ptr<ValueEditor> GetSelected();

    void Click();
    void Scroll(const int delta);

    void Render(Paint& paint, const int x, const int y, const int width);

private:
    std::shared_ptr<ValueEditor> UpdateSelection(const int delta);

private:
    sFONT& _font;
    uint8_t _selectedIdx;
    std::vector<std::shared_ptr<ValueEditor>> _editors;
};