#include "DynamicButtonField.h"
#include "Button.h"
#include "../../Runtime/Managers/CameraManager.h"
#include "../../Editor/GUI/RegisterActor.h"

DynamicButtonField::DynamicButtonField(const int& _id, const FString& _type, const Action& _callback)
{
	type = _type;
	callback = _callback;
	id = _id;
	std::string s = std::to_string(id);
	name = FString(type + " " + s.c_str());
}

void DynamicButtonField::MoveCamera()
{
	if (ImGui::IsMouseDoubleClicked(0))
	{
		if (!isOwner)
			return;
		/*
		cout << name.GetText() << endl;
		cout << "X: " << RegisterActor::GetInstance().GetActorPosition(id).X << endl;
		cout << "Y: " << RegisterActor::GetInstance().GetActorPosition(id).Y << endl;
		cout << "Z: " << RegisterActor::GetInstance().GetActorPosition(id).Z << endl;*/
		const FVector _vector = RegisterActor::GetInstance().GetActorPosition(id);
		CameraManager::GetInstance().SetPosition(_vector);
		isOwner = false;
	}
}

void DynamicButtonField::SelectActor()
{
	if (Button::MakeButton(name.GetText().c_str(), callback))
	{

		isOwner = true;
		RegisterActor::GetInstance().SetCurrentActor(id);
	}
	
	ImGui::SameLine(3,100);
	ImGui::Text(type.GetText().c_str());
}

void DynamicButtonField::Display()
{
	if (!callback)
		return;

	MoveCamera();
	SelectActor();
	

}
