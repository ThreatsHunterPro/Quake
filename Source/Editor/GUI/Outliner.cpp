#include "Outliner.h"
#include "Button.h"
#include "InputText.h"
void Outliner::Draw()
{
	
	ImGui::Text("Search");
	ImGui::InputText(" ", &expl, 50);
	ImGui::LabelText("Type", "Item label");

    
   
}
