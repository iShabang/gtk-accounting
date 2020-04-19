cmake_minimum_required(VERSION 3.12)

# set the project name
project(gtk-accounting)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (MY_COMPILE_FLAGS "-Wall" "-Wextra" "-Werror")

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  set (MY_COMPILE_FLAGS ${MY_COMPILE_FLAGS} "-DDEBUG_MODE")
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK gtkmm-3.0 REQUIRED)
pkg_check_modules(SQLITE sqlite3 REQUIRED)

add_subdirectory(src)
add_subdirectory(app)
