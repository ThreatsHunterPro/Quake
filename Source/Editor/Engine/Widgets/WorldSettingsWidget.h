#pragma once
#include "Source/Runtime/Core/Containers/TArray.h"
#include "Source/Editor/Engine/Widgets/PanelWidget.h"
#include "Source/Runtime/Objects/Actors/Lights/ALight.h"

class WorldSettingsWidget : public PanelWidget
{
private:
	FString name;
	EngineWindow* window;
	//ALight _light;

	TArray<char*, int> gameModeOverride;
	TArray<char*, int> defaultPawnClass;
	TArray<char*, int> hudClass;
	TArray<char*, int> playerControllerClass;
	TArray<char*, int> gameStateClass;
	TArray<char*, int> playerStateClass;
	TArray<char*, int> spectatorClass;

	bool precomputeVisibility = false;


	bool worldGravity = false;
	float globalGravityZ = 0.0f;

	float environmentIntensity = 0.0f;
	
public:
	WorldSettingsWidget(const FString& _name, EngineWindow* _window);
	~WorldSettingsWidget();

public:
	void Draw() override;
	void Stop() override;
};



