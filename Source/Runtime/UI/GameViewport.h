#pragma once
#include "Source/Runtime/Core/Containers/TMap.h"
#include "Source/Runtime/UI/Components/UUserWidget.h"
#include "Source/CoreMinimal.h"

class GameViewport
{
	TMap <std::string, UUserWidget* > viewportWidgetList;

public:
	FORCEINLINE static GameViewport& GetInstance()
	{
		static GameViewport _instance;
		return _instance;
	}

	FORCEINLINE uInt GetSize() const {
		return viewportWidgetList.Num();
	}

	bool IsWisgetAdded(const FString& _userWIdgetName) const;
	void DrawUI(sf::RenderWindow& _window);
	bool AddWidget(UUserWidget* _widget);
	void RemoveWidget(const FString& _userWidgetName);
	void ClearUI();
};