#pragma once
#include "Widget.h"

class ActiveWidget : public Widget
{
protected:
    bool widgetStatus;

public:
    void SetWidgetStatus(const bool _status) { widgetStatus = _status; }
    bool GetWidgetStatus() const { return widgetStatus; }
    
public:
    ActiveWidget() = default;
    ActiveWidget(const FString& _name, EngineWindow* _window);
};
