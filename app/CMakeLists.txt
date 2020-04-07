find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK gtk+-3.0 REQUIRED)

add_executable(gtk-accounting main.cpp)
target_include_directories(gtk-accounting PUBLIC ${GTK_INCLUDE_DIRS})
target_compile_features(gtk-accounting PRIVATE cxx_std_11)
target_link_libraries(gtk-accounting PRIVATE gtk-accounting-lib ${GTK_LIBRARIES})

