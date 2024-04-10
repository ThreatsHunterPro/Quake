#pragma once
#include "Source/Runtime/Core/Math/FVector/TVector.h"
#include "Source/Runtime/Core/Math/FVector/FVector2.h"
#include "Source/CoreMinimal.h"
#include <SFML/Graphics.hpp>
#include <functional>
 
typedef sf::Event::EventType ActionType;

enum  GameControllerButtons
{
	Cross = 1,
	Circle,
	Triangle,
	Square,
	L1,
	R1,
	L2,
	R2,
	LeftStick,
	RightStick,
};

enum  GameControllerAxes
{
	LeftStickX,
	LeftStickY,
};

struct InputData
{
	ActionType type;
	int key; 
	GameControllerButtons buttons;
	GameControllerAxes axes;

	InputData() = default;

 
	InputData(ActionType _type, int _key)
	{
		type = _type;
		key = _key;
	}
	InputData(ActionType _type, GameControllerAxes _axes)
	{
		type = _type;
		axes = _axes;
	}
};


struct ActionData
{ 
	string name;
	vector<InputData> keys;
	function<void()> callback;

	ActionData()
	{ 
		keys = vector<InputData>();
		callback = function<void()>();
	}

	template <class Class, typename RType = void, typename... Args>
	ActionData(string _name,  Class* _owner, RType(Class::* _callback)(Args...),
		const InputData& _primaryKey, const InputData& _secondaryKey = InputData(), Args... _args)
	{
		name = _name;
		callback = [_owner, _callback, _args...]() {
			return (_owner->*_callback)(_args...);
		};
		//callback = bind(_callback, _owner, _args);
		keys.push_back(_primaryKey);
		keys.push_back(_secondaryKey);
	}
	ActionData(string _name, const function<void()>& _callback,
		const InputData& _primaryKey, const InputData& _secondaryKey = InputData())
	{ 
		name = _name;
		callback = _callback;
		keys.push_back(_primaryKey);
		keys.push_back(_secondaryKey);
	}

	bool operator !() const
	{
		return callback == nullptr;
	} 
};

class ActionInput
{ 
	ActionData inputData;
public:
    //ActionInput(sf::Keyboard::Key _key, sf::Event::EventType _type, std::function<void()> _callback);
	ActionInput() = default;
    ActionInput(const ActionData& _data);
    
    void ProcessInput(const sf::Event& _event);

};
 