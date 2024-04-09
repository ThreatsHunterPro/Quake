#pragma once
#include "../../CoreMinimal.h"
#include "Button.h"
class DynamicButtonField
{
	FString name;
	std::function<void()> callback;
public:
	DynamicButtonField() { name = FString("name"); }
	DynamicButtonField(const FString& _name) { name = _name; }
	DynamicButtonField(const FString& _name, const std::function<void()>& _callback) { name = _name; callback = _callback; }
	void Display() 
	{ 
		if (!callback)
		{
			Button::MakeButton(name.GetText().c_str(), [&]()
				{

				});
			return;
		}
		Button::MakeButton(name.GetText().c_str(), callback);
	}
public:
	FORCEINLINE FString GetName() const { return name; }
};

