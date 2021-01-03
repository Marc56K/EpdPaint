#pragma once
#include <functional>
#include "ValueEditor.h"

class NumberEditor : public ValueEditor
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
    std::string GetValueAsString() const;
    double SetValue(const double value);

    bool IsEditing() const override;

    void Click() override;
    void ChangeValue(const int delta) override;

    int GetActualWidth() const override;
    int GetActualHeight() const override;
    void Render(Paint& paint, const int x, const int y) const override;

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