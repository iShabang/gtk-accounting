file(GLOB HEADER_LIST CONFIGURE_DEPENDS
    "${gtk-accounting_SOURCE_DIR}/include/gtk-accounting/*.h")

add_library(gtk-accounting-lib TestClass.cpp ${HEADER_LIST})
target_include_directories(gtk-accounting-lib PUBLIC ../include)
target_compile_features(gtk-accounting-lib PUBLIC cxx_std_11)
source_group(TREE "${PROJECT_SOURCE_DIR}/include" PREFIX "Header Files" FILES ${HEADER_LIST})
