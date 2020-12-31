#pragma once
#include <string>
#include <epdpaint.h>

class ValueEditor
{
public:
    ValueEditor(const std::string& name);
    virtual ~ValueEditor();

    const std::string& Name() const;

    bool IsSelected() const;
    virtual void Select();
    virtual void Deselect();

    virtual bool IsEditing() const;

    virtual void Click();
    virtual void ChangeValue(const int delta);

    virtual void Render(Paint& paint, const int x, const int y, sFONT& font) const = 0;

protected:
    const std::string _name;
    bool _selected;
};