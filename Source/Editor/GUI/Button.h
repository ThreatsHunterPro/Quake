#pragma once
#include "../../CoreMinimal.h"
#include < functional >
class Button
{

public:
    
    static bool MakeButton(const char* _label)
    {
        if (ImGui::Button(_label))
        {
            return true;
        }

        return false;
    }
    static bool MakeButton(const char* _label, const std::function<void()>& _callback)
    {
        if (ImGui::Button(_label))
        {
            _callback();
            return true;
        }

        return false;
    }
    
     static bool MakeButton(const char* _label, const std::function<void()>& _callback, ImVec2 _padding)
    {
         if (ImGui::Button(_label, _padding))
         {
             _callback();
             return true;
         }

         return false;
    }
    
};

