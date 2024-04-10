#pragma once

#include "Source/CoreMinimal.h"
#include "Source/Runtime/Core/Math/FVector/FVector2.h"

#include <SFML/Graphics.hpp>

enum EVisibility
{
	Visible = 0,	
	Hidden,
};

struct FWidgetTransform
{
	int posX, posY;

	FWidgetTransform(const int& _positionX = 0, const int& _positionY = 0)
	{
		posX = _positionX;
		posY = _positionY;
	}
};


class UWidget : public TObjectPtr
{

private:
	FString id;

protected:
	sf::Drawable* drawable = nullptr;
	FWidgetTransform renderTransform = (0,0);
	

public:
	bool bIsVariable = 1;
	bool bIsEnabled = 1;
	bool bOverride_Cursor = 1;
	bool bIsManagedByGameViewportSubsystem = 1;

	EVisibility Visibility = EVisibility::Visible;


public:
	FString GetID() const
	{
		return id;
	}

public:
	UWidget() = default;
	UWidget(const FString& _id);
	virtual ~UWidget() override;


public:
	virtual void Destroy();
	virtual void DrawWidget(sf::RenderWindow& _window);

	virtual void SetPosition(const FWidgetTransform& _transform);
	virtual void SetPosition(const uInt& _x, const uInt& _y);
	virtual FVector2 GetPosition() const = 0;
	virtual sf::Vector2f GetPositionSF() const = 0;

	
};