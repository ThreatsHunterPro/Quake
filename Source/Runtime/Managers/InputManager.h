#pragma once 
#include "..\..\CoreMinimal.h"
#include "..\Core\Math\FVector\FVector2.h"

#define genericCallback(Type, functionName)\
        [](GLFWwindow* window, auto ... arg) {\
            auto* pointer = static_cast<Type*>(glfwGetWindowUserPointer(window));\
            if(pointer) pointer->functionName(pointer, arg...);\
        }

class InputManager
{
    GLFWwindow* window;
    FVector2 previousCursorPos;

    std::function<void(InputManager*, double, double)> onWindowScrollCallback = [](auto self, double _a, double _b) { self->Scroll(_a, _a); };

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
    void BindCallbacks() const;
    void ProcessMouse();
    void ProcessInputs() const;


public:
    void Start(GLFWwindow* _window);
    void Scroll(double xoffset, double yoffset);
    void Update();
};