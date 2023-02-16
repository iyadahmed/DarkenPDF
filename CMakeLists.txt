cmake_minimum_required(VERSION 3.16)
project(DarkenPDF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PopplerCairo REQUIRED poppler-glib cairo)

# CLI
add_executable(DarkenPDF cli.cpp lib.hpp)
target_include_directories(DarkenPDF PRIVATE ${PopplerCairo_INCLUDE_DIRS})
target_link_libraries(DarkenPDF PRIVATE ${PopplerCairo_LIBRARIES})

# GUI
find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()
add_executable(DarkenPDF_GUI main.cpp main_window.cpp main_window.hpp)
target_include_directories(DarkenPDF_GUI PRIVATE ${PopplerCairo_INCLUDE_DIRS})
target_link_libraries(DarkenPDF_GUI PRIVATE Qt6::Widgets ${PopplerCairo_LIBRARIES})
set_target_properties(DarkenPDF_GUI PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
