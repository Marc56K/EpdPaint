#include "PropertyPage.h"
#include "MathUtils.h"

PropertyPage::PropertyPage() :
    _selectedIdx(-1)
{    
}

PropertyPage::~PropertyPage()
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
        if (_selectedIdx + delta < 0)
        {
            _selectedIdx = -1;
        }
        else
        {
            _selectedIdx = MathUtils::Modulo<int>(_selectedIdx + delta, _editors.size());
        }

        if (_selectedIdx < 0)
        {
            if (IsSelected()) Deselect();
        }
        else if (_selectedIdx < _editors.size() - 1)
        {
            if (!IsSelected()) Select();
        }

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
    else
    {
        _selectedIdx = 0;
        UpdateSelection(0);
    }
    
}

void PropertyPage::Scroll(const int delta)
{
    auto selected = GetSelected();
    if (selected != nullptr && delta != 0)
    {
        if (selected->IsEditing())
        {
            selected->Scroll(delta);
        }
        else
        {
            UpdateSelection(delta < 0 ? -1 : 1);
        }
    }
}

void PropertyPage::Render(Paint& paint, const int x, const int y)
{
    int yPos = y;
    for (auto editor : _editors)
    {
        editor->SetWdith(_width);
        const int h = editor->GetActualHeight() + 2;
        if ((yPos + h - y) > _height)
        {
            return;
        }
        editor->Render(paint, x, yPos);
        yPos += h;
    }
}