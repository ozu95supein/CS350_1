﻿cmake_minimum_required(VERSION 3.8)
project(cs350f21es_ass1)

############################
# Compiler options (for all targets)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (MSVC)
	add_compile_options(/W3 /D "_CRT_SECURE_NO_WARNINGS")
else ()
	add_compile_options(-Wall -Wextra -pedantic)
endif ()

add_subdirectory(src)
add_subdirectory(demo)
add_subdirectory(test)

# For VSCODE
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)
