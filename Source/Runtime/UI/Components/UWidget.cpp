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

void UWidget::SetPosition(const uInt& _x, const uInt& _y)
{
	renderTransform = (_x, _y);
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
