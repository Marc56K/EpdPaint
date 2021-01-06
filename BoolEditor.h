#pragma once
#include <functional>
#include "ValueEditor.h"

class BoolEditor : public ValueEditor
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

    void Click() override;
    void ChangeValue(const int delta) override;

    int GetActualWidth() const override;
    void Render(Paint& paint, const int x, const int y) const override;

private:
    bool _editing;
    bool _value;
    std::function<void(const bool)> _onValueChanged;
};