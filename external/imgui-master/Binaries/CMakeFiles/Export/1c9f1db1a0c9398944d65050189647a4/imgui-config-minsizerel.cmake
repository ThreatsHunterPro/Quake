#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "imgui::imgui" for configuration "MinSizeRel"
set_property(TARGET imgui::imgui APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(imgui::imgui PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/lib/imgui.lib"
  )

list(APPEND _cmake_import_check_targets imgui::imgui )
list(APPEND _cmake_import_check_files_for_imgui::imgui "${_IMPORT_PREFIX}/lib/imgui.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
