#include "GameViewport.h"

bool GameViewport::IsWisgetAdded(const FString& _userWIdgetName) const
{
    return viewportWidgetList.GetAllKeys().Contains((_userWIdgetName.GetText()));
}

void GameViewport::DrawUI(sf::RenderWindow& _window)
{
    for (UUserWidget* _widget : viewportWidgetList.GetAllValues())
    {
        if(_widget->Visibility == EVisibility::Visible)
            _widget->DrawUI(_window);
    }
}

bool GameViewport::AddWidget(UUserWidget* _widget)
{
    if (IsWisgetAdded(_widget->GetID()))
        return false;

    viewportWidgetList.Add(_widget->GetID().GetText(), _widget);
    return true;
}

void GameViewport::RemoveWidget(const FString& _userWidgetName)
{
    if (!IsWisgetAdded(_userWidgetName))
        return;

    viewportWidgetList.RemoveAt(_userWidgetName.GetText());
    //GarbageCollector::GetInstance().AddToCleanup<UUserWidget*>(_widget);
}

void GameViewport::ClearUI()
{
    for (UUserWidget* _widget : viewportWidgetList.GetAllValues())
    {
        _widget->Delete();
    }
}
