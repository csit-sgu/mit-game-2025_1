cmake_minimum_required(VERSION 3.10)
project (raygui C)

# Disable all warnings
if (MSVC)
    add_compile_options(/w)
else()
    add_compile_options(-w)
endif()

add_library (raygui STATIC src/raygui.c)
target_include_directories (raygui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries (raygui PUBLIC raylib)

