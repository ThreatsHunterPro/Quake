#include "CameraManager.h"
#include "TimerManager.h"
//#include "../Objects/Camera/UCamera.h"

void CameraManager::Register(UCamera* _camera)
{
	cameras.push_back(_camera);
}