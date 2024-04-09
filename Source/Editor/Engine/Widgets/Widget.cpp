#include "Widget.h"
#include "../Windows/Window.h"

Widget::Widget(const FString& _name, Window* _window)
{
    name = _name;
    window = _window;
}
Widget::~Widget()
{
    delete window;
}