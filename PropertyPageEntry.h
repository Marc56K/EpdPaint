#pragma once
#include <string>
#include "BaseControl.h"

class PropertyPageEntry : public BaseControl
{
public:
    PropertyPageEntry(const std::string& utf8name);
    virtual ~PropertyPageEntry();

    virtual const std::string& GetUtf8Name() const;

    virtual bool IsEditing() const;

    virtual void SetPadding(const int padding);

    virtual int GetActualWidth() const override;
    virtual int GetActualHeight() const override;
    virtual void Render(Paint& paint, const int x, const int y) override;

    static void GetColors(const bool selected, int* back, int* front);

protected:
    const std::string _utf8name;
    const std::string _latin1name;
    int _padding;
};