#include "PlaceActorsWidget.h"

PlaceActorsWidget::PlaceActorsWidget(const FString& _name, EngineWindow* _window) :
	PanelWidget(_name, _window)
{
	typeFilter = EActorType::ALL_CLASSES;

	filterButtons =
	{
		new Button("Basic", [this]
		{
			typeFilter = EActorType::BASIC;
		}),
		new Button("Lights", [this]
		{
			typeFilter = EActorType::LIGHTS;
		}),
		new Button("Shapes", [this]
		{
			typeFilter = EActorType::SHAPES;
		}),
		new Button("All classes", [this]
		{
			typeFilter = EActorType::ALL_CLASSES;
		})
	};

	actorsButtons =
	{
		// ============== BASIC ===========================
		new ActorsButton("Actor", EActorType::BASIC, [this]
		{
			// CALLBACK
		}),
		new ActorsButton("Character", EActorType::BASIC, [this]
		{
			// CALLBACK
		}),
		new ActorsButton("Pawn", EActorType::BASIC, [this]
		{
			// CALLBACK
		}),

		// ============== LIGHTS ===========================
		new ActorsButton("Directional Light", EActorType::LIGHTS, [this]
		{
			// CALLBACK
		}),
		new ActorsButton("Point Light", EActorType::LIGHTS, [this]
		{
			// CALLBACK
		}),
		new ActorsButton("Spot Light", EActorType::LIGHTS, [this]
		{
			// CALLBACK
		}),

		// ============== SHAPES ===========================
		new ActorsButton("Cube", EActorType::SHAPES, [this]
		{
			// CALLBACK
		})

	};
}

PlaceActorsWidget::~PlaceActorsWidget()
{
	for (int i = 0; i < filterButtons.size(); i++)
	{
		delete filterButtons[i];
	}

	for (int i = 0; i < actorsButtons.size(); i++)
	{
		delete actorsButtons[i];
	}

	filterButtons.clear();
	actorsButtons.clear();
}

void PlaceActorsWidget::Draw()
{
	// FILTER
	ImGui::SetNextWindowSize(ImVec2(500, 500));
	ImGui::Begin("Place Actors", &widgetStatus);

	ImGui::Text("Search classes :");
	ImGui::SameLine();
	search.Draw(" ", 250.f);
	
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

	ImGui::Text(*EnumToString(typeFilter));

	////////////////////////////////////////////////////////////////////
	// ACTORS FILTERED

	const int _actorButtonsCount = actorsButtons.size();
	for (int _buttonIndex = 0; _buttonIndex < _actorButtonsCount; _buttonIndex++)
	{
		ActorsButton* _button = actorsButtons[_buttonIndex];
		if (!_button) continue;

		if (!search.PassFilter(*(_button->GetTitle())))
		{
			if (_button->GetTitle().Contains(search.InputBuf))
			{
				if (ImGui::Button(*(_button->GetTitle())))
				{
					_button->Callback();
				}
			}
		}

		else if (_button->GetActorType() == typeFilter)
		{
			if (ImGui::Button(*(_button->GetTitle())))
			{
				_button->Callback();
			}
		}
		else if (typeFilter == EActorType::ALL_CLASSES)
		{
			if (ImGui::Button(*(_button->GetTitle())))
			{
				_button->Callback();
			}
		}
	}

	ImGui::End();
}

void PlaceActorsWidget::Stop()
{
}
