cmake_minimum_required(VERSION 3.16)
project(DarkenPDF)

set(CMAKE_CXX_STANDARD 17)

add_executable(DarkenPDF main.cpp lib.hpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PopplerCairo REQUIRED poppler-glib cairo)

target_include_directories(DarkenPDF PRIVATE ${PopplerCairo_INCLUDE_DIRS})
target_link_libraries(DarkenPDF PRIVATE ${PopplerCairo_LIBRARIES})
