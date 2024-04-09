#include "PlaceActorsWidget.h"

PlaceActorsWidget::PlaceActorsWidget(const FString& _name, EngineWindow* _window) :
	PanelWidget(_name, _window)
{
	filterButtons =
	{
		new Button("All Classes", [this]
		{
			
		}),
		new Button("Test", [this]
		{
			cout << "TEST" << endl;
		})
	};

	actorsButtons =
	{
		new Button("Actor", [this]
		{
			cout << "PLACE ACTOR" << endl;
		}),
		new Button("Character", [this]
		{
			cout << "PLACE CHARACTER" << endl;
		}),
		new Button("PointLight", [this]
		{
			cout << "PLACE POINT LIGHT" << endl;
		})

	};
}

PlaceActorsWidget::~PlaceActorsWidget()
{
	filterButtons.empty();
}

void PlaceActorsWidget::Draw()
{
	// FILTER
	ImGui::SetNextWindowSize(ImVec2(500, 500));
	ImGui::Begin("Place Actors", &widgetStatus);

	//if (ImGui::Button("Actor"))
	//{
	//	cout << "SPAWN ACTOR" << endl;
	//}
	
	const int _filterButtonsCount = filterButtons.size();
	for (int _buttonIndex = 0; _buttonIndex < _filterButtonsCount; _buttonIndex++)
	{
		Button* _button = filterButtons[_buttonIndex];
		if (!_button) continue;

		if (ImGui::Button(*(_button->GetTitle())))
		{
			_button->Callback();
		}

		if (_buttonIndex != _filterButtonsCount - 1)
			ImGui::SameLine();
	}
	
	////////////////////////////////////////////////////////////////////

	ImGui::Text("Basic");
	ImGui::ShowDemoWindow();

	////////////////////////////////////////////////////////////////////
	// ACTORS FILTERED

	const int _actorButtonsCount = actorsButtons.size();
	for (int _buttonIndex = 0; _buttonIndex < _actorButtonsCount; _buttonIndex++)
	{
		Button* _button = actorsButtons[_buttonIndex];
		if (!_button) continue;

		if (ImGui::Button(*(_button->GetTitle())))
		{
			_button->Callback();
		}
	}

	ImGui::End();
}

void PlaceActorsWidget::Stop()
{
}
