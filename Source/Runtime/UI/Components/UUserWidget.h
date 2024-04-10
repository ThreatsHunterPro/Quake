#pragma once

#include "Source/Runtime/Core/Containers/TMap.h"
#include "Source/Runtime/Objects/UObject.h"
#include "UWidget.h"


class UUserWidget : TObjectPtr
{

private:
	TMap<string, UWidget*> widgets;
	FString id = "";
	
public:
	int Priority = 0;
	bool bIsFocusable = false;
	EVisibility Visibility = EVisibility::Hidden;
	

public:
	FORCEINLINE FString GetID() const 
	{
		return id;
	}

public:
	UUserWidget(const FString& _id, const TArray<UWidget*>& _listWidget = {});
	virtual ~UUserWidget() override;
	

protected:
	void Initialize();
	virtual void NativeConstruct();
	virtual void NativeDestruct();

public:
	void AddToViewport();
	void RemoveFromViewport();
	void Delete();
	void DrawUI(sf::RenderWindow& _window);
	void CreateWidget(UWidget* _widget);
	void RemoveWidget(const FString& _widgetName);
	
	template<typename T>
	T* GetWidget(const FString& _widgetName)
	{
		return dynamic_cast<T*>(*widgets.Find(_widgetName.GetText()));
	}
};