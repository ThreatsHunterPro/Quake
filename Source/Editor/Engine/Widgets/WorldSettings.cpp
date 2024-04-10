#include "WorldSettings.h"

WorldSettingsWidget::WorldSettingsWidget(const FString& _name, EngineWindow* _window) : PanelWidget(_name,_window)
{
	name = _name;
	window = _window;
	
}

WorldSettingsWidget::~WorldSettingsWidget()
{
}

void WorldSettingsWidget::Draw()
{
	ImGui::ShowDemoWindow();
	ImGui::Begin("World Settings");

	/*if (ImGui::CollapsingHeader("Precomputed Visibility"))
	{
		ImGui::Checkbox("Precompute Visibility", &precomputeVisibility);
	}*/
	if (ImGui::CollapsingHeader("Game Mode"))
	{
		ImGui::PushItemWidth(80);
		static int gameModeOverrideItem = -1;
		ImGui::Combo("GameMode Override", &gameModeOverrideItem, gameModeOverride.begin(), gameModeOverride.Num());
		if (ImGui::TreeNode("Selected GameMode"))
		{
			ImGui::PushItemWidth(80);
			static int defaultPawnClassItem = -1;
			ImGui::Combo("Default Pawn Class", &defaultPawnClassItem, defaultPawnClass.begin(), defaultPawnClass.Num());
			static int hudClassItem = -1;
			ImGui::Combo("HUD Class", &hudClassItem, hudClass.begin(), hudClass.Num());
			static int playerControllerClassItem = -1;
			ImGui::Combo("Player Controller Class", &playerControllerClassItem, playerControllerClass.begin(), playerControllerClass.Num());
			static int gameStateClassItem = -1;
			ImGui::Combo("Game State Class", &gameStateClassItem, gameStateClass.begin(), gameStateClass.Num());
			static int playerStateClassItem = -1;
			ImGui::Combo("Player State Class", &playerStateClassItem, playerStateClass.begin(), playerStateClass.Num());
			static int spectatorClassItem = -1;
			ImGui::Combo("Spectator Class", &spectatorClassItem, spectatorClass.begin(), spectatorClass.Num());
			ImGui::TreePop();
			ImGui::Spacing();
		}

	}
	if (ImGui::CollapsingHeader("Lightmass"))
	{
		if (ImGui::TreeNode("Lightmass Settings"))
		{

			ImGui::TreePop();
			ImGui::Spacing();
		}
	}
	if (ImGui::CollapsingHeader("Rendering"))
	{

	}
	if (ImGui::CollapsingHeader("Audio"))
	{

	}

	/*if (ImGui::CollapsingHeader("Physics"))
	{
	}
	if (ImGui::CollapsingHeader("NetWork"))
	{
	}
	if (ImGui::CollapsingHeader("Tick"))
	{
	}
	if (ImGui::CollapsingHeader("Level Instance"))
	{
	}*/

	ImGui::End();
}


void WorldSettingsWidget::Stop()
{
}
