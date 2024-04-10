#include "UWidget.h"


UWidget::UWidget(const FString& _id)
{
	id = _id;
}

UWidget::~UWidget()
{
	Destroy();
}

void UWidget::SetPosition(const FWidgetTransform& _transform)
{
	renderTransform = _transform;
}

void UWidget::SetPosition(const int& _x, const int& _y)
{
	renderTransform = FWidgetTransform(_x, _y);
}

void UWidget::Destroy()
{
	if (drawable) {
		delete drawable;
		drawable = nullptr;
	}
}

void UWidget::DrawWidget(sf::RenderWindow& _window)
{
	_window.draw(*drawable);
}
