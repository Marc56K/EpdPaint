#pragma once
#include <functional>
#include "ValueEditor.h"

class StringEditor : public ValueEditor
{
public:
    StringEditor(
        const std::string& name,
        const std::string& value,
        std::function<void(const std::string&)> onValueChanged = nullptr);
    virtual ~StringEditor();

    const std::string& GetValue() const;
    void SetValue(const std::string& value);

    bool IsEditing() const override;

    void Click() override;
    void Scroll(const int delta) override;

    void Render(Paint& paint, const int x, const int y) override;

private:
    int _editIdx;
    bool _editChar;
    std::string _value;
    std::function<void(const std::string&)> _onValueChanged;
};