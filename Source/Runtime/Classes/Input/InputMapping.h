#pragma once
#include <Source/CoreMinimal.h>
#include <SFML/Graphics.hpp>
//	InputManager::GetInstance().AddMapping(this);
class ActionInput;
class InputMapping
{
    vector<ActionInput> allActions;
    void Register();
public:
    InputMapping(const initializer_list<ActionInput>& _inputs);
    void ProcessInput(const sf::Event& _event);
};