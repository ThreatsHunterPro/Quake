#include "ActionInput.h"

 
ActionInput::ActionInput(const ActionData& _data)
{
	inputData = _data;
}

void ActionInput::ProcessInput(const sf::Event& _event)
{
	for (const InputData& _data : inputData.keys)
	{
		if (_event.type == _data.type && _event.key.code == _data.key)
		{
			if (inputData.callback)
				inputData.callback();
		}
	}
 
}
