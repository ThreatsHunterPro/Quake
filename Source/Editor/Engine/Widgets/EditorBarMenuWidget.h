#include "Widget.h"
#include "../Controls/Menu.h"

class EditorBarMenuWidget : public Widget
{
    vector<Menu> menus;

public:
    EditorBarMenuWidget(const FString& _name, EngineWindow* _window);
    ~EditorBarMenuWidget() override;

public:
    void Draw() override;
    void ExecuteCallback(const FString& _methodName) const;
    void Stop() override;
};
