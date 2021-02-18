#pragma once
#include <functional>
#include "PropertyPageEntry.h"

class ActionButton : public PropertyPageEntry
{
public:
    ActionButton(
        const std::string& name,
        std::function<void(void)> onClick);
    virtual ~ActionButton();

    bool IsEditing() const override;

    bool Click() override;
    bool Scroll(const int delta) override;

    void Render(Paint& paint, const int x, const int y) override;

private:
    bool _value;
    std::function<void(void)> _onClick;
};