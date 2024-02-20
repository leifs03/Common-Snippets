cmake_minimum_required(VERSION 3.25)

project()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    if(MSVC)
        target_compile_options(
            ${PROJECT_NAME} PRIVATE
            -Ox
        )
    else()
        target_compile_options(
            ${PROJECT_NAME} PRIVATE
            -Wall
            -O3
        )
    endif()
else()
    if(MSVC)
        target_compile_options(
            ${PROJECT_NAME} PRIVATE
            -Od
            -DEBUG
        )
    else()
        target_compile_options(
            ${PROJECT_NAME} PRIVATE
            -Wall
            -O0
            -g
        )
    endif()
endif()

