#pragma once 
#include "../../CoreMinimal.h"

class UCamera;

class CameraManager
{
	vector<UCamera*> cameras;

public:
	static CameraManager& GetInstance()
	{
		static CameraManager _instance;
		return _instance;
	}
	vector<UCamera*> GetCameras() const { return cameras; }

public:
	void Register(UCamera* _camera);

};