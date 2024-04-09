#include "DetailsWindow.h"

DetailsWindow::DetailsWindow(const FString& _name, EngineWindow* _window) : PanelWidget(_name, _window)
{
	buttons =
	{
		new Button("New Blueprint Script Component...", [this] {ExecuteCallback("New Blueprint Script Component..."); }),
	};
}
DetailsWindow::~DetailsWindow()
{
	buttons.empty();
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
		const int _buttonsCount = buttons.size();
		for (int _buttonIndex = 0; _buttonIndex < _buttonsCount; _buttonIndex++)
		{
			Button* _button = buttons[_buttonIndex];
			if (ImGui::MenuItem(*(_button->GetTitle()), *(_button->GetShortcut())))
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
	if (ImGui::BeginListBox(""))
	{
		const bool _select = 0;
		if (ImGui::Selectable("test", _select))
			cout << "select" << endl;

		ImGui::EndListBox();
	}
#pragma endregion

#pragma region transform

#pragma endregion
	ImGui::End();
}
void DetailsWindow::ExecuteCallback(const FString& _methodName) const
{
	cout << _methodName.GetText().c_str() << endl;
}
void DetailsWindow::Stop()
{
}
