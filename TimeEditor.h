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
        std::function<void(const uint8_t hh, const uint8_t mm)> onTimeChanged = nullptr);
    virtual ~TimeEditor();

    void GetTime(uint8_t& hh, uint8_t& mm) const;
    std::string GetTimeComponentAsString(const uint8_t timeComponent) const;
    void SetTime(const uint8_t hh, const uint8_t mm);

    bool IsEditing() const override;

    void Click() override;
    void ChangeValue(const int delta) override;

    int GetActualWidth() const override;
    void Render(Paint& paint, const int x, const int y) const override;

private:
    uint8_t _hh;
    uint8_t _mm;
    std::function<void(const uint8_t hh, const uint8_t mm)> _onTimeChanged;
    uint8_t _editingIdx;
};