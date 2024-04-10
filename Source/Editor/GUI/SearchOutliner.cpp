#include "Outliner.h"
#include "InputText.h"
#include "SearchOutliner.h"


void SearchOutliner::Draw()
{
	
    ImGui::Text("Search");

    InputText::MakeInputField(*expl.c_str(), 30, [&]()
        {
            expl = expl.c_str();
        });
}
