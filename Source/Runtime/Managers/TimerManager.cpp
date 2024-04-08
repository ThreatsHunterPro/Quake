#include "TimerManager.h"

TimerManager::TimerManager()
{
    deltaTime = 0.0f;
    lastTime = 0.0f;
}


void TimerManager::Update()
{
    const float _currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = _currentFrame - lastTime;
    lastTime = _currentFrame;
}