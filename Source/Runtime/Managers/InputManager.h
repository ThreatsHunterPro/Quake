#pragma once 
#include "..\..\CoreMinimal.h"
#include "..\Core\Math\FVector\FVector2.h"
#include "Source/Runtime/Core/Math/FVector/TVector.h"
#include <SFML/Graphics.hpp>

#define genericCallback(Type, functionName)\
        [](GLFWwindow* window, auto ... arg) {\
            auto* pointer = static_cast<Type*>(glfwGetWindowUserPointer(window));\
            if(pointer) pointer->functionName(pointer, arg...);\
        }
 
class InputMapping;
class InputManager
{
    sf::RenderWindow* window;
    FVector2 previousCursorPos;

    std::function<void(InputManager*, double, double)> onWindowScrollCallback = [](auto self, double _a, double _b) { self->Scroll(_a, _a); };
    TArray<InputMapping*> allMappings;
public:
    FORCEINLINE static InputManager& GetInstance()
    {
        static InputManager _instance;
        return _instance;
    }

public:
    InputManager();
    void AddMapping(InputMapping* _mapping);
    void ClearMappings();
private:
    void InitControls() const;
    void BindCallbacks() const;
    void ProcessMouse();
    void ProcessInputs() const;


public:
    void Start(sf::RenderWindow* _window);
    void Scroll(double xoffset, double yoffset);
    void Update();
};