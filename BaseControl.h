#pragma once
#include "epdpaint.h"

class BaseControl
{
public:
    BaseControl();
    virtual ~BaseControl();
    virtual void SetFont(sFONT& font);
    virtual bool IsSelected() const;
    virtual void Select();
    virtual void Deselect();
    virtual void Click();
    virtual void Scroll(const int delta);
    virtual void SetWdith(const int width);
    virtual void SetHeight(const int height);
    virtual int GetActualWidth() const;
    virtual int GetActualHeight() const;
    virtual void Render(Paint& paint, const int x, const int y) = 0;

protected:
    sFONT& _font;
    bool _selected;
    int _width;
    int _height;
};