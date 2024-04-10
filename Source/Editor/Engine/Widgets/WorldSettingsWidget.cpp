#include "WorldSettingsWidget.h"

WorldSettingsWidget::WorldSettingsWidget(const FString& _name, EngineWindow* _window) : PanelWidget(_name,_window)
{
	name = _name;
	window = _window;
	//environmentIntensity = _light.GetIntensity();
	//worldGravity = UWorld::GetWorldGravity();
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
			ImGui::SliderFloat("Environment Intensity", (float*)&environmentIntensity, 0.0f, 10.0f, "%0f");
			//_light->SetIntensity(environmentIntensity);
			ImGui::TreePop();
			ImGui::Spacing();
		}
	}
	/*if (ImGui::CollapsingHeader("Audio"))
	{

	}*/
	if (ImGui::CollapsingHeader("Physics"))
	{
		ImGui::Checkbox("Override World Gravity", &worldGravity);
		ImGui::SliderFloat("Global Gravity Z", (float*)&globalGravityZ, -100.0f, 100.0f, "%0f");
		//GetWorld()->SetGravity(globalGravity);

	}
	/*
	if (ImGui::CollapsingHeader("NetWork"))
	{
	}
	if (ImGui::CollapsingHeader("Tick"))
	{
		ImGui::SliderFloat2("Min Global Time Dilation", (float*)&environmentIntensity, 0.0f, 100000.0f, "%.0001f");
		ImGui::SliderFloat2("Max Global Time Dilation", (float*)&environmentIntensity, 0.0f, 100000.0f, "%20f");
		ImGui::SliderFloat2("Min Undilated Frame Time", (float*)&environmentIntensity, 0.0f, 100000.0f, "%.0005f");
		ImGui::SliderFloat2("Max Undilated Frame Time", (float*)&environmentIntensity, 0.0f, 100000.0f, "%.4f");
	}
	if (ImGui::CollapsingHeader("Level Instance"))
	{
	}*/

	ImGui::End();
}


void WorldSettingsWidget::Stop()
{
}
