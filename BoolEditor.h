#pragma once
#include <functional>
#include "PropertyPageEntry.h"

class BoolEditor : public PropertyPageEntry
{
public:
    BoolEditor(
        const std::string& name,
        const bool value,
        std::function<void(const bool)> onValueChanged = nullptr);
    virtual ~BoolEditor();

    bool GetValue() const;
    bool SetValue(const bool value);

    bool IsEditing() const override;

    bool Click() override;
    bool Scroll(const int delta) override;

    void Render(Paint& paint, const int x, const int y) override;

private:
    bool _value;
    std::function<void(const bool)> _onValueChanged;
};