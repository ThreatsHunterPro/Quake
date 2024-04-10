#include "PlaceActorsWidget.h"

PlaceActorsWidget::PlaceActorsWidget(const FString& _name, EngineWindow* _window) :
	PanelWidget(_name, _window)
{

}

void PlaceActorsWidget::Draw()
{
	//Update

	ImGui::SetNextWindowSize(ImVec2(500, 500));
	ImGui::Begin("Place Actors", &widgetStatus);

	if (ImGui::Button("Actor"))
	{
		cout << "SPAWN ACTOR" << endl;
	}

	ImGui::End();
}

void PlaceActorsWidget::Stop()
{
}
