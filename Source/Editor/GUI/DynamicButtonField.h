#pragma once
#include "../../CoreMinimal.h"
typedef  std::function<void()> Action;
class DynamicButtonField
{
private:
	
	int id;
	FString name; 
	FString type;
	Action callback;
	bool isOwner = false;
public:
	DynamicButtonField(const int& _id, const FString& _type, const Action& _callback);
	void MoveCamera();
	void SelectActor();
	void Display();
public:
	FORCEINLINE  int GetID() const  { return id; }
	FORCEINLINE FString GetName() const { return name; }
	FORCEINLINE void SetName(const FString& _name)  { name = _name; }
};

