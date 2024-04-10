#pragma once
#include "../../CoreMinimal.h"
#include "../../Runtime/Core/Containers/FString.h"

class EngineWindow;

class Widget
{
protected:
    FString name;
    EngineWindow* window;

public:
    FORCEINLINE void SetName(const FString& _name) { name = _name; }
    FORCEINLINE FString GetName() const { return name; }
    
public:
    Widget() = default;
    Widget(const FString& _name, EngineWindow* _window);

public:
    virtual void Draw() = 0;
    virtual void Stop() = 0;
};