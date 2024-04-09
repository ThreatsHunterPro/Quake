#include "Outliner.h"
#include "Button.h"
#include "InputText.h"
Outliner::~Outliner()
{
    shader = nullptr;
}
void Outliner::Start(GLFWwindow* _window)
{
    Widget::Start(_window);
    Init(_window);
}
void Outliner::Init(GLFWwindow* _window, CustomShader* elementShader)
{
    shader = elementShader;
    for (size_t i = 0; i < 25; i++)
    {
        char* temp;
        if (shader)
        {
            std::string strData = std::to_string(elementShader->GetShaderID());
            char* temp = new char[strData.length() + 1];
            strcpy(temp, strData.c_str());
        }
        temp = "test";
        field.push_back(new DynamicButtonField
        (
            FString(temp),
            [&]()
            {
                if (!shader)
                    return;
                shader->Use();
                shader->SetVec4("newColor", FVector4(1, 1, 1, 1.0f));
            }
        ));
    }
}
void Outliner::Start(GLFWwindow* _window, CustomShader* elementShader)
{
    Widget::Start(_window, elementShader);
    Init(_window, elementShader);
}

void Outliner::Draw()
{
    ImGui::Begin("OutLiner");

    ImGui::Text("Search");
 
    InputText::MakeInputField(*expl.c_str(), 30 , [&]()
        {
            expl = expl.c_str();
        });
  
    ImGui::LabelText("Type", "Item label");

    if (ImGui::BeginTabBar("OutLinerBar"))
    {
        
      
       
        for (int i = 0; i < field.size(); i++)
            if (expl.size()== 0)  
            {
               
                field[i]->Display();
            }
            else if(field[i]->GetName().GetText().find(expl) != string::npos)
            {
                field[i]->Display();
            }
        
        ImGui::EndTabBar();

    }
   
   
    ImGui::End();
}
