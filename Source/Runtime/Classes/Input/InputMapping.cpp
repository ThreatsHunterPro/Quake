#include "InputMapping.h"
#include "../../Managers/InputManager.h"

void InputMapping::Register()
{
	InputManager::GetInstance().AddMapping(this);
}

InputMapping::InputMapping(const TArray<ActionInput*>& _inputs)
{
	Register();
	allActions.Append(_inputs);
}
