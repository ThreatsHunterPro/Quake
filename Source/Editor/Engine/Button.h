#pragma once
#include "Macros.h"
#include <vector>

class Button
{
protected:
    FString title;
    FString shortcut;
    Event<> event;
    vector<Button*> children;
    
public:
    FORCEINLINE FString GetTitle() const { return title; }
    FORCEINLINE FString GetShortcut() const { return shortcut; }
    FORCEINLINE vector<Button*> GetChildren() { return children; }
    FORCEINLINE void Callback() { return event.Invoke(); }
    
public:
    Button();
    Button(const FString& _title, Action _callback = nullptr, const FString& _shortcut = "", const vector<Button*>& _button = vector<Button*>());
    ~Button();

    bool operator==(const Button& _button) const
    {
        return _button.GetTitle() == title;
    }
    bool operator!=(const Button& _button) const
    {
        return _button.GetTitle() != title;
    }
    bool operator!() const
    {
        return !event.IsBound();
    }
};