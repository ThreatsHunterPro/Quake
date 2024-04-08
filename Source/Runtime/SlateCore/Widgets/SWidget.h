#pragma once
#include "Source/CoreMinimal.h"

enum ESlateVisibility
{
	All,
	Collapsed,
	Hidden,
	HitTestInvisible,
	SelfHitTestInvisible,
	Visible
};

class SWidget
{
	float renderOpacity = 1;
	TWeakPtr<SWidget> parentWidgetPtr;
	ESlateVisibility visibility;
public:

	//SWidget SWidgetConstruct(const FSlateBaseNamedArgs&)
};