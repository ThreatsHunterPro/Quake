#include "DetailsWindow.h"

DetailsWindow::DetailsWindow(const FString& _name, EngineWindow* _window) : PanelWidget(_name, _window)
{
	buttons =
	{
		new Button("Static Mesh", [this] {ExecuteCallback("Static Mesh"); }),
	};
}
DetailsWindow::~DetailsWindow()
{
	buttons.clear();
}
void DetailsWindow::Draw()
{
	ImGui::SetNextWindowSize(ImVec2(500, 500));
	ImGui::Begin("Details", &widgetStatus);

#pragma region textNameObject
	ImGui::Text("Get object name");
#pragma endregion

	ImGui::ShowDemoWindow();

#pragma region bouton add
	ImGui::SameLine(0, 50);
	if (ImGui::Button("Add"))
		ImGui::OpenPopup("Add_popup");
	if (ImGui::BeginPopup("Add_popup"))
	{
		//TODO Add search bar
		const int _buttonsCount = buttons.size();
		for (int _buttonIndex = 0; _buttonIndex < _buttonsCount; _buttonIndex++)
		{
			Button* _button = buttons[_buttonIndex];
			if (ImGui::Selectable(*_button[_buttonIndex].GetTitle()))
			{
				_button->Callback();
			}
		}
		ImGui::EndPopup();
	}
#pragma endregion

#pragma region searchBar

#pragma endregion

#pragma region parentage
	if (ImGui::BeginListBox(" "))
	{
		int _item_current_index = 0;
		int _count = buttons.size();
		for (int i = 0; i < _count; i++)
		{
			const bool _is_selected = (_item_current_index == i);
			if (ImGui::Selectable(*buttons[i]->GetTitle(), _is_selected))
			{
				_item_current_index = i;
				cout << "select" << endl;
			}
			if (_is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndListBox();
	}
#pragma endregion

#pragma region transform
	if (ImGui::TreeNode("Transform"))
	{
		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.10f);
#pragma region Location
		static float posX = 0;
		static float posY = 0;
		static float posZ = 0;
		ImGui::Text("Location");
		ImGui::SameLine(0, 25);
		ImGui::DragFloat("X", &posX, 0.005f); //TODO change value by get position
		ImGui::SameLine(0, 25);
		ImGui::DragFloat("Y", &posY, 0.005f); //TODO change value by get position
		ImGui::SameLine(0, 25);
		ImGui::DragFloat("Z", &posZ, 0.005f); //TODO change value by get position
#pragma endregion
#pragma region Rotation
		static float rotX = 0;
		static float rotY = 0;
		static float rotZ = 0;
		ImGui::Text("Rotation");
		ImGui::SameLine(0, 25);
		ImGui::DragFloat("X ", &rotX, 0.005f); //TODO change value by get position
		ImGui::SameLine(0, 18);
		ImGui::DragFloat("Y ", &rotY, 0.005f); //TODO change value by get position
		ImGui::SameLine(0, 18);
		ImGui::DragFloat("Z ", &rotZ, 0.005f);
#pragma endregion
#pragma region Scale
		static float scaleX = 0;
		static float scaleY = 0;
		static float scaleZ = 0;
		ImGui::Text("Scale");
		ImGui::SameLine(0, 46);
		ImGui::DragFloat("X  ", &scaleX, 0.5f); //TODO change value by get position
		ImGui::SameLine(0, 11);
		ImGui::DragFloat("Y  ", &scaleY, 0.5f); //TODO change value by get position
		ImGui::SameLine(0, 11);
		ImGui::DragFloat("Z  ", &scaleZ, 0.5f);
#pragma endregion
#pragma region Mobility
		static int _index = 0;
		ImGui::Text("Mobility");
		ImGui::SameLine(0, 25);
		ImGui::RadioButton("Static", &_index, 0); 
		ImGui::SameLine();
		ImGui::RadioButton("Stationary", &_index, 1); 
		ImGui::SameLine();
		ImGui::RadioButton("Movable", &_index, 2);
#pragma endregion
		ImGui::TreePop();
	}
#pragma endregion
	ImGui::End();
}
void DetailsWindow::ExecuteCallback(const FString& _methodName) const
{
	cout << "callback" << endl;
}
void DetailsWindow::Stop()
{
}
