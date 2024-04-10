#pragma once
#include "Widget.h"
#include "ContentField.h"

class SearchOutliner : public Widget
{
	string expl;
	
public:
	void Draw() override;
	FORCEINLINE string GetExpl()const { return expl; }
};

