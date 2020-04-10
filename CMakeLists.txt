cmake_minimum_required(VERSION 3.12)

# set the project name
project(gtk-accounting)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK gtkmm-3.0 REQUIRED)
pkg_check_modules(SIGC sigc++-3.0 REQUIRED)
pkg_check_modules(SQLITE sqlite3 REQUIRED)

add_subdirectory(src)
add_subdirectory(app)
