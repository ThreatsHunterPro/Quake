#include "UUserWidget.h"
#include "UWidget.h"
#include "../GameViewport.h"


UUserWidget::UUserWidget(const FString& _id, const TArray<UWidget*>& _listWidget)
{
	id = _id;

	size_t _size = _listWidget.Num();
	for (int i = 0; i < _size; i++)
	{
		UWidget* _wid = _listWidget[i];
		CreateWidget(_wid);
	}

	NativeConstruct();
}

UUserWidget::~UUserWidget()
{
	NativeDestruct();
}

void UUserWidget::AddToViewport()
{	
	Visibility = EVisibility::Visible;
}


void UUserWidget::Initialize()
{
	GameViewport::GetInstance().AddWidget(this);
}

void UUserWidget::NativeConstruct()
{
	Initialize();
}

void UUserWidget::NativeDestruct()
{	
	for (UWidget* _widget : widgets.GetAllValues())
	{
		delete _widget;
		_widget = nullptr;
	}
	
	widgets.Empty();
	RemoveFromViewport();
	GameViewport::GetInstance().RemoveWidget(id);
}

void UUserWidget::RemoveFromViewport()
{	
	Visibility = EVisibility::Hidden;
}

void UUserWidget::Delete()
{
	NativeDestruct();
	delete this;
}

void UUserWidget::DrawUI(sf::RenderWindow& _window)
{
	for (UWidget* _widget : widgets.GetAllValues())
	{
		if(_widget->Visibility == EVisibility::Visible)
			_widget->DrawWidget(_window);
	}
}

void UUserWidget::CreateWidget(UWidget* _widget)
{
	widgets.Add(_widget->GetID().GetText(), _widget);
}

void UUserWidget::RemoveWidget(const FString& _widgetName)
{
	for (UWidget* _widget : widgets.GetAllValues())
	{
		if (_widget->GetID() == _widgetName)
		{
			_widget->Destroy();
			widgets.RemoveAt(_widgetName.GetText());
		}
	}
}
