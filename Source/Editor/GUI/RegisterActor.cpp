#pragma once
#include "RegisterActor.h"

void RegisterActor::Display() const
{
	for (auto _actualId : idActors)
	{
		cout << "actorsID: " << _actualId << endl;
	}
}

bool RegisterActor::Contains(const int& _id)
{
	for (auto _actualId : idActors)
	{
		if(_id== _actualId)
			return true;
	}
	return false;
}

void RegisterActor::Add(const int& _id)
{
	int id = 0;
	if (Contains(_id))
	{
		id = id * id + idActors.size();
		
		idActors.push_back(id);
		return;
	}
	idActors.push_back(_id);
}
