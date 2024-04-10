#include "Outliner.h"
#include "Button.h"
#include "InputText.h"
#include "../../Editor/GUI/RegisterActor.h"



Outliner::Outliner()
{
    contentField = new ContentField();
    searchOutliner = new SearchOutliner();
}

Outliner::~Outliner()
{
    delete  contentField;
    delete searchOutliner;
}

void Outliner::Start(GLFWwindow* _window)
{
    Widget::Start(_window);
    if(contentField)
    contentField->Init(_window);
}



void Outliner::Draw()
{
    ImGui::Begin("OutLiner");

    if (searchOutliner)
        searchOutliner->Draw();
 
    if (contentField && searchOutliner)
        contentField->Draw(searchOutliner->GetExpl());
   
    ImGui::End();
}
