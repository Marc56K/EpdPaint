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
    PropertyPage(std::function<void()> onEditingFinished = nullptr);
    ~PropertyPage();

    void Add(std::shared_ptr<PropertyPageEntry> editor);

    std::shared_ptr<PropertyPageEntry> GetSelected();

    virtual bool Click() override;
    virtual bool Scroll(const int delta) override;

    virtual void Render(Paint& paint, const int x, const int y) override;

private:
    std::shared_ptr<PropertyPageEntry> UpdateSelection(const int delta);

private:
    int _selectedIdx;
    std::function<void()> _onEditingFinished;
    std::vector<std::shared_ptr<PropertyPageEntry>> _editors;    
};