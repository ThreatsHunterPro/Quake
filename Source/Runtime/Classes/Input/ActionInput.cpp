#include "ActionInput.h"

ActionInput::ActionInput(sf::Keyboard::Key _key, sf::Event::EventType _type,std::function<void(const FInputActionValue&)> _callback)
{
	inputData.key = _key;
	callback = _callback;
	type = _type;
	inputType = InputType::Keyboard;
}

ActionInput::ActionInput(sf::Mouse::Button _button, sf::Event::EventType _type, std::function<void(const FInputActionValue&)> _callback)
{
	inputData.mouseButton = _button;
	callback = _callback;
	type = _type;
	inputType = InputType::Mouse;
}

void ActionInput::ProcessInput(const sf::Event& _event)
{
	
	if (_event.type == type)
	{
		if (inputType == InputType::Keyboard && _event.key.code == inputData.mouseButton
			|| inputType == InputType::Mouse && _event.key.code == inputData.mouseButton)
		{
			callback(FInputActionValue(true));
		}
	}
 
}
