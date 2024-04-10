#include "ContentField.h"
#include "RegisterActor.h"

void ContentField::Start(GLFWwindow* _window)
{
	Widget::Start(_window);
	Init(_window);
}
void ContentField::Init(GLFWwindow* _window)
{
    char* temp;

    const size_t actors = RegisterActor::GetInstance().Count()/2;
  
    for (int i = 0; i < actors; i++)
    {

       
        temp = "Cube";
        field.push_back(
            new DynamicButtonField
            (
                i,
                FString(temp),
                [&]()
                {


                }
            )
        );
    }
}


void ContentField::Draw(string& _expl)
{
  
    //ImGui::LabelText("Type", "Item label");

    if (ImGui::BeginTabBar("OutLinerBar"))
    {
      
       // ImGui::TableSetupColumn("Label name");
       // ImGui::TableSetupColumn("Type");
       // ImGui::TableHeadersRow();
        for (int i = 0; i < field.size(); i++)
            if (_expl.size() == 0)
                field[i]->Display();
            else if (field[i]->GetName().GetText().find(_expl) != string::npos)
                field[i]->Display();

        ImGui::EndTabBar();

    }
    
}