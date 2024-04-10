#include "InputMapping.h"
#include "../../Managers/InputManager.h"
#include "ActionInput.h"

void InputMapping::Register()
{
	InputManager::GetInstance().AddMapping(this);
}

InputMapping::InputMapping(const initializer_list<ActionInput>& _inputs)
{
	Register();
	//allActions.insert(allActions.cend(), _inputs);
	allActions.insert(allActions.cend(), _inputs);
}

void InputMapping::ProcessInput(const sf::Event& _event)
{
	for (ActionInput _action : allActions)
	{
		_action.ProcessInput(_event);
	}
}
