#include "PropertyPage.h"

PropertyPage::PropertyPage(sFONT& font) :
    _font(font), _selectedIdx(0)
{    
}

void PropertyPage::Add(std::shared_ptr<ValueEditor> editor)
{
    if (editor != nullptr)
    {
        editor->SetFont(_font);
        _editors.push_back(editor);
        UpdateSelection(0);
    }
}

std::shared_ptr<ValueEditor> PropertyPage::GetSelected()
{
    return UpdateSelection(0);
}

std::shared_ptr<ValueEditor> PropertyPage::UpdateSelection(const int delta)
{
    std::shared_ptr<ValueEditor> result = nullptr;
    if (!_editors.empty())
    {
        _selectedIdx = (_selectedIdx + delta) % _editors.size();
        for (int i = 0; i < _editors.size(); ++i)
        {
            auto editor = _editors[i];
            if (i == _selectedIdx)
            {
                editor->Select();
                result = editor;
            }
            else
            {
                editor->Deselect();
            }
        }
    }
    return result;
}

void PropertyPage::Click()
{
    auto selected = GetSelected();
    if (selected != nullptr)
    {
        selected->Click();
    }
}

void PropertyPage::Scroll(const int delta)
{
    auto selected = GetSelected();
    if (selected != nullptr && delta != 0)
    {
        if (selected->IsEditing())
        {
            selected->ChangeValue(delta);
        }
        else
        {
            UpdateSelection(delta < 0 ? 1 : -1);
        }
    }
}

void PropertyPage::Render(Paint& paint, const int x, const int y, const int width)
{
    int yPos = y;
    for (auto editor : _editors)
    {
        editor->SetWdith(width);
        editor->Render(paint, x, yPos);
        yPos += editor->GetActualHeight() + 2;
    }
}