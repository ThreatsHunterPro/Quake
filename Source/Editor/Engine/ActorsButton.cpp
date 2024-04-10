#include "ActorsButton.h"

ActorsButton::ActorsButton()
{
	title = "Actor Button";
}

ActorsButton::ActorsButton(const FString& _title, const EActorType& _actorType, Action _callback, const FString& _shortcut, const vector<Button*>& _button) :
	Button(_title, _callback, _shortcut, _button)
{
	title = _title;
	actorType = _actorType;
	event = Event<>(_callback);
	shortcut = _shortcut;
	children = _button;
}

ActorsButton::~ActorsButton()
{
	
}
