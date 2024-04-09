#pragma once
#define INLINE			__inline
#define FORCEINLINE		__forceinline
#define SUPER			__super

#define CHECK_PTR(ptr, ...)	if (!ptr) return VA_ARGS
#define MAX	std::max

// #define PATH_CONTENT "D:/C/UnirealGit/Unireal/Content/"
// #define PATH_TEXTURES String("D:/C/UnirealGit/Unireal/Content/Textures/")
// #define PATH_SHADERS String("D:/C/UnirealGit/Unireal/Content/Shaders/")
// #define PATH_MODELS String("D:/C/UnirealGit/Unireal/Content/Models/")

#define PATH_CONTENT "D:/Prog/OpenGL/Unireal/Content/"
#define PATH_TEXTURES "D:/Prog/OpenGL/Unireal/Content/Textures/"
#define PATH_SHADERS "D:/Prog/OpenGL/Unireal/Content/Shaders/"
#define PATH_MODELS "D:/Prog/OpenGL/Unireal/Content/Models/"

#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <filesystem>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../ImGUI/imgui.h"
#include "../../ImGUI/imgui_impl_opengl3.h"
#include "../../ImGUI/imgui_impl_glfw.h"

#include "Event.h"