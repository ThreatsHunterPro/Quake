#pragma once
#include <Source/CoreMinimal.h>
//	InputManager::GetInstance().AddMapping(this);
class ActionInput;
class InputMapping
{
    TArray<ActionInput*> allActions;
    void Register();
public:
    InputMapping(const TArray<ActionInput*>& _inputs);

};