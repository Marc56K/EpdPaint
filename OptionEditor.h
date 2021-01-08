#pragma once
#include <functional>
#include <vector>
#include "ValueEditor.h"

class OptionEditor : public ValueEditor
{
public:
    OptionEditor(
        const std::string& name,
        const std::vector<std::string>& options,
        const uint8_t selectedIdx,
        std::function<void(const uint8_t, const std::string&)> onValueChanged = nullptr);
    virtual ~OptionEditor();

    uint8_t GetSelectedIdx() const;
    void SetSelectedIdx(const uint8_t selectedIdx);

    const std::string& GetValue() const;

    bool IsEditing() const override;

    void Click() override;
    void Scroll(const int delta) override;

    void Render(Paint& paint, const int x, const int y) const override;

private:
    std::vector<std::string> _options;
    uint8_t _selectedIdx;
    std::function<void(const uint8_t, const std::string&)> _onValueChanged;
    bool _editing;
};