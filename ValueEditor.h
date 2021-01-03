#pragma once
#include <string>
#include <epdpaint.h>

class ValueEditor
{
public:
    ValueEditor(const std::string& name);
    virtual ~ValueEditor();

    virtual const std::string& GetName() const;

    virtual bool IsSelected() const;
    virtual void Select();
    virtual void Deselect();

    virtual bool IsEditing() const;

    virtual void Click();
    virtual void ChangeValue(const int delta);

    virtual void SetFont(sFONT& font);
    virtual void SetWdith(const int width);
    virtual void SetHeight(const int height);
    virtual void SetPadding(const int padding);
    virtual int GetActualWidth() const = 0;
    virtual int GetActualHeight() const = 0;
    virtual void Render(Paint& paint, const int x, const int y) const = 0;

protected:
    const std::string _name;
    bool _selected;

    sFONT& _font;
    int _width;
    int _height;
    int _padding;
};