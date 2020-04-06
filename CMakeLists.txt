cmake_minimum_required(VERSION 3.10)

# set the project name
project(gtk-accounting)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK gtk+-3.0 REQUIRED)

include_directories(CMAKE_CURRENT_SOURCE_DIR/headers/gtk-accounting)
include_directories(${GTK_INCLUDE_DIRS})

# add the executable
add_executable(gtk-accounting 
               src/main.cpp)
target_link_libraries(gtk-accounting ${GTK_LIBRARIES})
