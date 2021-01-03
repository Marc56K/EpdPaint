#include "ValueEditor.h"

ValueEditor::ValueEditor(const std::string& name) :
    _name(name),
    _selected(false),
    _font(Font12),
    _width(-1),
    _height(-1),
    _padding(2)
{    
}

ValueEditor::~ValueEditor()
{    
}

const std::string& ValueEditor::GetName() const
{
    return _name;
}

bool ValueEditor::IsSelected() const
{
    return _selected;
}

void ValueEditor::Select()
{
    _selected = true;
}

void ValueEditor::Deselect()
{
    _selected = false;
}

bool ValueEditor::IsEditing() const
{
    return false;
}

void ValueEditor::Click()
{
}

void ValueEditor::ChangeValue(const int delta)
{
}

void ValueEditor::SetFont(sFONT& font)
{
    _font = font;
}

void ValueEditor::SetWdith(const int width)
{
    _width = width;
}

void ValueEditor::SetHeight(const int height)
{
    _height = height;
}

void ValueEditor::SetPadding(const int padding)
{
    _padding = padding;
}