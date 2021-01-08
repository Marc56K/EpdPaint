#pragma once
#include <functional>
#include "ValueEditor.h"

class TimeEditor : public ValueEditor
{
public:
    TimeEditor(
        const std::string& name,
        const uint8_t hh,
        const uint8_t mm,
        std::function<void(const uint8_t hh, const uint8_t mm)> onValueChanged = nullptr);
    virtual ~TimeEditor();

    void GetValue(uint8_t& hh, uint8_t& mm) const;
    void SetValue(const uint8_t hh, const uint8_t mm);

    bool IsEditing() const override;

    void Click() override;
    void Scroll(const int delta) override;

    void Render(Paint& paint, const int x, const int y) const override;

private:
    uint8_t _hh;
    uint8_t _mm;
    std::function<void(const uint8_t hh, const uint8_t mm)> _onValueChanged;
    uint8_t _editMode;
};