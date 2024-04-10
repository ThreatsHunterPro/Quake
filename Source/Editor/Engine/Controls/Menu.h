#pragma once
#include "Button.h"
#include "Source/CoreMinimal.h"

struct Menu
{
    FString Title;
    vector<Button*> Buttons;
    vector<int> Separators;

    Menu()
    {
        Title = "";
        Buttons = vector<Button*>();
    }
    Menu(const FString& _title, const vector<Button*>& _buttons, const vector<int>& _separators = vector<int>())
    {
        Title = _title;
        Buttons = _buttons;
        Separators = _separators;
    }
};