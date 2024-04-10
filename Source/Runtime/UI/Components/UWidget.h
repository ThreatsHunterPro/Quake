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
	float sizeX, sizeY;

	FWidgetTransform(const int& _positionX, const int& _positionY)
	{
		posX = _positionX;
		posY = _positionY;
		sizeX = 0;
		sizeY = 0;
	}
	FWidgetTransform(const float& _positionX, const float& _positionY, const float& _sizeX, const float& _sizeY)
	{
		posX = _positionX;
		posY = _positionY;
		sizeX = _sizeX;
		sizeY = _sizeY;
	}
};


class UWidget : public TObjectPtr
{

private:
	FString id;

protected:
	sf::Drawable* drawable = nullptr;
	FWidgetTransform renderTransform = FWidgetTransform(0,0);
	

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
	virtual void SetPosition(const int& _x, const int& _y);
	virtual FVector2 GetPosition() const = 0;
	virtual sf::Vector2f GetPositionSF() const = 0;

	
};