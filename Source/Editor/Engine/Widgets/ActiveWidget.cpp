#include "ActiveWidget.h"

ActiveWidget::ActiveWidget(const FString& _name, Window* _window) : Widget(_name, _window)
{
    widgetStatus = true;
}
ActiveWidget::~ActiveWidget()
{
    
}
