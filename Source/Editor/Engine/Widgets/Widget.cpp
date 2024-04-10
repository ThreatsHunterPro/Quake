#include "Widget.h"
#include "../EngineWindow.h"

Widget::Widget(const FString& _name, EngineWindow* _window)
{
    name = _name;
    window = _window;
}
Widget::~Widget()
{
    //delete window;
}