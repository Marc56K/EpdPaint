#include "BaseControl.h"

BaseControl::BaseControl() :
    _font(Font12),
    _selected(false),
    _width(0),
    _height(0)
{
}

BaseControl::~BaseControl()
{
}

void BaseControl::SetFont(sFONT& font)
{
}

bool BaseControl::IsSelected() const
{
    return _selected;
}

void BaseControl::Select()
{
    _selected = true;
}

void BaseControl::Deselect()
{
    _selected = false;
}

bool BaseControl::Click()
{
    return false;
}

bool BaseControl::Scroll(const int delta)
{
    return false;
}

void BaseControl::SetWdith(const int width)
{
    _width = width;
}

void BaseControl::SetHeight(const int height)
{
    _height = height;
}

int BaseControl::GetActualWidth() const
{
    return _width;
}

int BaseControl::GetActualHeight() const
{
    return _height;
}