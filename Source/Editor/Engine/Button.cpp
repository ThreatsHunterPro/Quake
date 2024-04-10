#include "Button.h"

Button::Button()
{
    title = "ButtonTitle";
    shortcut = "";
    event = Event<>();
    children = vector<Button*>();
}
Button::Button(const FString& _title, Action _callback, const FString& _shortcut, const vector<Button*>& _button)
{
    title = _title;
    shortcut = _shortcut;
    event = Event<>(_callback);
    children = _button;
}
Button::~Button()
{
    children.clear();
}