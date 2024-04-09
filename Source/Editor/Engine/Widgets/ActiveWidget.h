#pragma once
#include "Widget.h"

class ActiveWidget : public Widget
{
protected:
    bool widgetStatus;
    
public:
    ActiveWidget(const FString& _name, Window* _window);
    ~ActiveWidget() override;
};
