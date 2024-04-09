#pragma once
#include "Button.h"
#include "../../../Core/Macros.h"

struct Menu
{
    String Title;
    Array<Button*> Buttons;
    Array<int> Separators;

    Menu()
    {
        Title = "";
        Buttons = Array<Button*>();
    }
    Menu(const String& _title, const Array<Button*>& _buttons, const Array<int>& _separators = Array<int>())
    {
        Title = _title;
        Buttons = _buttons;
        Separators = _separators;
    }
};