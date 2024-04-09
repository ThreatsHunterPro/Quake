#pragma once
#include "Source/CoreMinimal.h"

class Window;

class Widget
{
protected:
    FString name;
    Window* window;

public:
    FORCEINLINE void SetName(const FString& _name) { name = _name; }
    FORCEINLINE FString GetName() const { return name; }
    
public:
    Widget(const FString& _name, Window* _window);
    virtual ~Widget();

public:
    virtual void Draw() = 0;
    virtual void Stop() = 0;
};