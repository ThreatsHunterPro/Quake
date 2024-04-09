#pragma once
#include "ActiveWidget.h"

class PanelWidget : public ActiveWidget
{
public:
    PanelWidget(const FString& _name, EngineWindow* _window);
    ~PanelWidget() override;
};
