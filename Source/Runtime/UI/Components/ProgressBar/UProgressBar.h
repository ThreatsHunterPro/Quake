#pragma once
#include "../UWidget.h"

enum ProgressType
{
	PT_CENTER,
	PT_LEFT,
	PT_TOP,
	PT_RIGHT,
	PT_BOTTOM,

	PT_COUNT
};

class UProgressBar : public UWidget
{
private:
	sf::Color foregroundColor;
	sf::Color backgroundColor;
	float currentValue;
	float maxValue;
	sf::RectangleShape* fillBar;
	sf::RectangleShape* backgroundBar;
	ProgressType orientationBar;


public:

public:
	UProgressBar(const FString& _id, FWidgetTransform _transform, ProgressType _orientation = ProgressType::PT_LEFT, const float& _maxValue = 100.f, const sf::Color& _fillColor = sf::Color::Green, const sf::Color _backgroundColor = sf::Color::White);
	~UProgressBar();


private:
	void InitBackgroundBar();
	void InitFillBar();

public:
	void SetPercent(float _value);
	void SetMaxValue(const float& _maxValue);
	void SetSize(const FWidgetTransform& _transform);
	void SetSize(const float& _x, const float& _y);


	virtual void SetPosition(const FWidgetTransform& _transform) override;
	virtual void SetPosition(const int& _x, const int& _y) override;
	virtual FVector2 GetPosition() const override;
	virtual sf::Vector2f GetPositionSF() const override;
	virtual void DrawWidget(sf::RenderWindow& _window) override;
};