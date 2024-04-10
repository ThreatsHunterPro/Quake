#pragma once
#include <iostream>
#include <functional>
#include <list>

#include "Runtime/Core/Containers/FString.h"
#include "Runtime/Core/Containers/TArray.h"
#include "Editor/Pointers/TWeakPtr.h"
#include "Editor/GarbageCollector/GarbageCollector.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "common/shader.hpp"
#include "Source/Runtime/Core/Math/MathFwd.h"

#include "Source/ImGUI/imgui.h"
#include "Source/ImGUI/imgui_impl_glfw.h"
#include "Source/ImGUI/imgui_impl_opengl3.h"

// OBJECTS MACRO.H
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#define BASE __super
#define FORCEINLINE __forceinline

using namespace std;
using namespace glm;
