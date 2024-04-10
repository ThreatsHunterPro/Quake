#pragma once 
#include "..\..\CoreMinimal.h"

class InputManager
{
    GLFWwindow* window;
    vec2 previousCursorPos;

public:
    FORCEINLINE static InputManager& GetInstance()
    {
        static InputManager _instance;
        return _instance;
    }

public:
    InputManager();

private:
    void InitControls() const;
    void ProcessMouse();
    void ProcessInputs() const;

public:
    void Start(GLFWwindow* _window);
    void Update();
};