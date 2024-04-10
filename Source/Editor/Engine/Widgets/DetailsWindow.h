#pragma once
#include "PanelWidget.h"
#include "Source/Editor/Engine/Controls/Button.h"
#include "Source/CoreMinimal.h"
#include <Source/Editor/Engine/Controls/Menu.h>
#include <Source/Runtime/Objects/UObject.h>

class DetailsWindow : public PanelWidget
{
    vector<Button*> buttons;

public:
    DetailsWindow(const FString& _name, EngineWindow* _window);
    ~DetailsWindow() override;

public:
    void Draw() override;
    void ExecuteCallback(const FString& _methodName) const;
    void Stop() override;
};