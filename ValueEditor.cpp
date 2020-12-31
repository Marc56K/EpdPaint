#include "ValueEditor.h"

ValueEditor::ValueEditor(const std::string& name) :
    _name(name),
    _selected(false)
{    
}

ValueEditor::~ValueEditor()
{    
}

const std::string& ValueEditor::Name() const
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