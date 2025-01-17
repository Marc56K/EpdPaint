#pragma once
#include <functional>
#include "PropertyPageEntry.h"

class NumberEditor : public PropertyPageEntry
{
public:
    NumberEditor(
        const std::string& name,
        const std::string& unit,
        const int decimalPlaces,
        const double stepSize,
        const double minValue, 
        const double maxValue, 
        const double value,
        std::function<void(const double)> onValueChanged = nullptr);
    virtual ~NumberEditor();

    double GetValue() const;
    void SetValue(const double value);

    bool IsEditing() const override;

    bool Click() override;
    bool Scroll(const int delta) override;

    void Render(Paint& paint, const int x, const int y) override;

private:
    const std::string _unit;
    const int _decimalPlaces;
    const double _stepSize;
    const double _minValue;
    const double _maxValue;
    bool _editing;
    double _value;
    std::function<void(const double)> _onValueChanged;
};