cmake_minimum_required(VERSION 3.8)

project(ion)

if(MSVC)
	add_definitions(-DUNICODE -D_UNICODE)
	add_compile_options(/W4 /WX)
else()
	add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

file(GLOB COMPILER_SOURCES CONFIGURE_DEPENDS "src/compiler/*.cpp")
file(GLOB UTILS_SOURCES CONFIGURE_DEPENDS "src/utils/*.cpp")

add_executable (compiler ${COMPILER_SOURCES} ${UTILS_SOURCES})

target_precompile_headers(compiler PUBLIC include/pch.hpp)
set_property(TARGET compiler PROPERTY CXX_STANDARD 23)
include_directories(compiler include)