#pragma once
#include "Widget.h"

class ActiveWidget : public Widget
{
protected:
    bool widgetStatus;
    
public:
    ActiveWidget(const FString& _name, EngineWindow* _window);
    ~ActiveWidget() override;
};
