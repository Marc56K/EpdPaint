#pragma once
#include <memory>
#include <vector>
#include "NumberEditor.h"
#include "TimeEditor.h"
#include "BoolEditor.h"
#include "StringEditor.h"
#include "OptionEditor.h"

class PropertyPage : public BaseControl
{
public:
    PropertyPage();
    ~PropertyPage();

    void Add(std::shared_ptr<ValueEditor> editor);

    std::shared_ptr<ValueEditor> GetSelected();

    virtual void Click() override;
    virtual void Scroll(const int delta) override;

    virtual void Render(Paint& paint, const int x, const int y) override;

private:
    std::shared_ptr<ValueEditor> UpdateSelection(const int delta);

private:
    int _selectedIdx;
    std::vector<std::shared_ptr<ValueEditor>> _editors;
};