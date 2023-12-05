cmake_minimum_required(VERSION 3.25)

project()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

add_executable(
    ${PROJECT_NAME}
    ./src/main.cpp
)

#find_package(
#    SDL2 REQUIRED
#)

#find_package(
#    fmt REQUIRED
#)

#target_include_directories(
#    ${PROJECT_NAME} PRIVATE
#    ${SDL2_INCLUDE_DIRS}
#    ${fmt_INCLUDE_DIRS}
#)

#target_link_libraries(
#    ${PROJECT_NAME} PRIVATE
#    ${SDL2_LIBRARIES}
#    fmt::fmt
#)

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

