add_executable(gtk-accounting
               main.cpp
               MenuBox.cpp
               InfoBox.cpp
               Builder.cpp
               Facade.cpp
               Table.cpp
               AddTransactionPopup.cpp
               FilterWindow.cpp
               FilterBox.cpp)
target_include_directories(gtk-accounting PUBLIC ${GTK_INCLUDE_DIRS})
target_compile_features(gtk-accounting PRIVATE cxx_std_11)
target_compile_options(gtk-accounting PRIVATE ${MY_COMPILE_FLAGS})
target_link_libraries(gtk-accounting PRIVATE gtk-accounting-lib ${GTK_LIBRARIES})

