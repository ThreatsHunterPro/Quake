#include "EditorBarMenuWidget.h"

EditorBarMenuWidget::EditorBarMenuWidget(const FString& _name, EngineWindow* _window) : Widget(_name, _window)
{
	menus =
	{
		Menu("File",
		{
			new Button("New Level...", [this] { ExecuteCallback("NewLevel"); }),
			new Button("Open Level...", [this] { ExecuteCallback("OpenLevel"); }),
			new Button("Open Asset...[Disable]", [this] { ExecuteCallback("OpenAsset"); }),
			new Button("Save Level", [this] { ExecuteCallback("SaveLevel"); }),
			new Button("New Project...", [this] { ExecuteCallback("NewProject"); }),
			new Button("Open Project...", [this] { ExecuteCallback("OpenProject"); })
	
		}),
		Menu("Edit",
			{
				new Button("Editor Preferences...", [this] { ExecuteCallback("EditorPreferences"); }),
				new Button("Project Settings...", [this] { ExecuteCallback("ProjectSettings"); })
			}),
		Menu("Window",
			{
				/*new Button("Scene", [_window]
				{
					_window->AddWidget(new RenderPanelWidget("Scene", _window));
				}),
				new Button("Game", [_window]
				{
					_window->AddWidget(new RenderPanelWidget("Game", _window));
				}),*/
				new Button("Hierarchy", [this] { ExecuteCallback("Hierarchy"); }),
				new Button("Inspector", [this] { ExecuteCallback("Inspector"); })
			}),

	};
};

EditorBarMenuWidget::~EditorBarMenuWidget()
{
	for (size_t i = 0; i < menus.size(); i++)
	{
		for (size_t j = 0; j < menus[i].Buttons.size(); j++)
		{
			delete menus[i].Buttons[j];
		}
	}
	menus.clear();
}

void EditorBarMenuWidget::Draw()
{
	if (ImGui::BeginMainMenuBar())
	{
		const int _menusCount = menus.size();
		for (int _menuIndex = 0; _menuIndex < _menusCount; _menuIndex++)
		{
			Menu _menu = menus[_menuIndex];
			if (ImGui::BeginMenu(_menu.Title.GetText().c_str()))
			{
				vector<Button*> _buttons = _menu.Buttons;
				const int _buttonsCount = _buttons.size();
				for (int _buttonIndex = 0; _buttonIndex < _buttonsCount; _buttonIndex++)
				{
					Button* _button = _buttons[_buttonIndex];
					if (ImGui::MenuItem(_button->GetTitle().GetText().c_str(), _button->GetShortcut().GetText().c_str()))
					{
						_button->Callback();
					}
				}
				ImGui::EndMenu();
			}
			ImGui::SameLine();
		}
		ImGui::EndMainMenuBar();
	}
}

void EditorBarMenuWidget::ExecuteCallback(const FString& _methodName) const
{
	cout << _methodName.GetText() << endl;
}

void EditorBarMenuWidget::Stop()
{
}
