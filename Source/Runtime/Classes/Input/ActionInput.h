#pragma once
#include "Source/Runtime/Core/Math/FVector/TVector.h"
#include "Source/Runtime/Core/Math/FVector/FVector2.h"
#include "Source/CoreMinimal.h"
#include <SFML/Graphics.hpp>
#include <functional>
enum class EInputActionValueType : uint8
{
    Boolean,
    Axis1D,
    Axis2D,
    Axis3D,
};

struct FInputActionValue
{
    EInputActionValueType type;

private:
    FVector3d Value;

public:
    FInputActionValue(bool _v) : Value(_v, 0, 0) { type = EInputActionValueType::Boolean; }
    FInputActionValue(float _v) : Value(_v,0,0) { type = EInputActionValueType::Axis1D;    }
    FInputActionValue(FVector2 _v) : Value(_v.X, _v.Y, 0) { type = EInputActionValueType::Axis2D; }
    FInputActionValue(FVector3d _v) : Value(_v) { type = EInputActionValueType::Axis3D; }

    template<typename T>
    inline T Get() const { return T(); }
};
#pragma region overloads
template<>
inline bool FInputActionValue::Get() const
{
    return Value.Length() > 0;
}
template<>
inline float FInputActionValue::Get() const
{
    return Value.X;
}
template<>
inline FVector2 FInputActionValue::Get() const
{
    return FVector2(Value.X, Value.Y);
}
template<>
inline FVector3d FInputActionValue::Get() const
{
    return Value;
}

#pragma endregion


union InputData
{
    sf::Keyboard::Key key;
    sf::Mouse::Button mouseButton;
};
enum InputType
{
    Keyboard,
    Mouse
};

class ActionInput
{
    std::function<void(const FInputActionValue&)> callback;
    InputType inputType;
    InputData inputData;
    sf::Event::EventType type;
public:
    ActionInput(sf::Keyboard::Key _key, sf::Event::EventType _type, std::function<void(const FInputActionValue&)> _callback);
    ActionInput(sf::Mouse::Button _button, sf::Event::EventType _type,  std::function<void(const FInputActionValue&)> _callback);
    
    void ProcessInput(const sf::Event& _event);

};
 