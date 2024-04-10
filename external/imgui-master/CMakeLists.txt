cmake_minimum_required(VERSION 3.20)
project(imgui)

set(IMGUI_DIR "D:/p2vs/QuakeGit/Quake/external/imgui-master")

if(NOT IMGUI_DIR)
	message(FATAL_ERROR "IMGUI_DIR must be set to the imgui root directory")
endif()

set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED)

set(ROOT ${IMGUI_DIR})

add_library(imgui STATIC
	${ROOT}/imgui.cpp
	${ROOT}/imgui.h
	${ROOT}/imstb_rectpack.h
	${ROOT}/imstb_textedit.h
	${ROOT}/imstb_truetype.h
    ${ROOT}/imgui_demo.cpp
    ${ROOT}/imgui_draw.cpp
    ${ROOT}/imgui_internal.h
    ${ROOT}/imgui_tables.cpp
    ${ROOT}/imgui_widgets.cpp
)
target_include_directories(imgui PUBLIC
    $<BUILD_INTERFACE:${ROOT}>
    $<INSTALL_INTERFACE:include>)
	
set(INSTALL_TARGETS imgui)
set(INSTALL_HEADERS ${ROOT}/imgui.h ${ROOT}/imconfig.h)

install(TARGETS ${INSTALL_TARGETS}
    EXPORT imgui-targets DESTINATION lib)
install(EXPORT imgui-targets
    FILE imgui-config.cmake
    NAMESPACE imgui::
    DESTINATION lib/cmake/imgui)
install(FILES ${INSTALL_HEADERS}
    DESTINATION include)

