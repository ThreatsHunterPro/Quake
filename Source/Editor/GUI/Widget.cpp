#include "Widget.h"
#include "../Engine/EngineWindow.h"

Widget::Widget(const FString& _name, EngineWindow* _window)
{
    name = _name;
    window = _window;
}