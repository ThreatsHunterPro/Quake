#include "UProgressBar.h"
#include "Source/Runtime/Core/Math/FMath.h"

UProgressBar::UProgressBar(const FString& _id, FWidgetTransform _transform, ProgressType _orientation, const float& _maxValue, const sf::Color& _fillColor, const sf::Color _backgroundColor) : UWidget(_id)
{
	currentValue = _maxValue;
	maxValue = _maxValue;
	foregroundColor = _fillColor;
	backgroundColor = _backgroundColor;
	orientationBar = _orientation;
	renderTransform = _transform;

	InitFillBar();
	InitBackgroundBar();

	SetPercent((currentValue * 100.f) / maxValue);
}

void UProgressBar::InitBackgroundBar()
{
	backgroundBar = new  sf::RectangleShape(sf::Vector2f(renderTransform.sizeX, renderTransform.sizeY));

	backgroundBar->setOutlineThickness(2);
	backgroundBar->setOutlineColor(backgroundColor);

	backgroundBar->setPosition(renderTransform.posX, renderTransform.posY);
}

void UProgressBar::InitFillBar()
{
	fillBar = new sf::RectangleShape(sf::Vector2f(renderTransform.sizeX, renderTransform.sizeY));

	fillBar->setFillColor(foregroundColor);

	fillBar->setPosition(renderTransform.posX, renderTransform.posY);
}

UProgressBar::~UProgressBar()
{
	delete fillBar;
	delete backgroundBar;
	fillBar = nullptr;
	backgroundBar = nullptr;
}

void UProgressBar::SetPercent(float _percent)
{
	FMath::Clamp(_percent, 0.f, maxValue);

	currentValue = _percent;
	switch (orientationBar)
	{
	case PT_CENTER:
		//TODO plus tard ?
		break;
	case PT_LEFT:
		fillBar->setSize(sf::Vector2f(renderTransform.sizeX * (_percent / 100), renderTransform.sizeY));
		break;
	case PT_TOP:

		break;
	case PT_RIGHT:

		break;
	case PT_BOTTOM:

		break;
	default:
		std::cout << "Orientation cannot be null." << std::endl;
		break;
	}
}

void UProgressBar::SetMaxValue(const float& _maxValue)
{
	maxValue = _maxValue;
}

void UProgressBar::SetPosition(const FWidgetTransform& _transform)
{
	SetPosition(_transform.posX, _transform.posY);
}

void UProgressBar::SetPosition(const int& _x, const int& _y)
{
	UWidget::SetPosition(_x, _y);

	backgroundBar->setPosition(_x, _y);
	fillBar->setPosition(_x, _y);
}

void UProgressBar::SetSize(const FWidgetTransform& _transform)
{
	SetSize(_transform.sizeX, _transform.sizeY);
}

void UProgressBar::SetSize(const float& _x, const float& _y)
{
	renderTransform.sizeX = _x;
	renderTransform.sizeY = _y;
	backgroundBar->setSize(sf::Vector2f(_x, _y));
}

FVector2 UProgressBar::GetPosition() const
{
	sf::Vector2f _pos = GetPositionSF();
	return FVector2(_pos.x, _pos.y);
}

sf::Vector2f UProgressBar::GetPositionSF() const
{
	return fillBar->getPosition();
}

void UProgressBar::DrawWidget(sf::RenderWindow& _window)
{
	_window.draw(*backgroundBar);
	_window.draw(*fillBar);
}
