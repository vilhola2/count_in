cmake_minimum_required(VERSION 3.1)

project(count_in C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

add_compile_options(
    -Wall
    -Wextra
    -Wno-pedantic
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g -O0)
else()
    add_compile_options(-O2 -DNDEBUG)
endif()

set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL"
    "${CMAKE_CURRENT_BINARY_DIR}/SDL"
    EXCLUDE_FROM_ALL
)

set(SDL3MIXER_TESTS OFF CACHE BOOL "" FORCE)
set(SDL3MIXER_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/external/SDL_mixer"
    "${CMAKE_CURRENT_BINARY_DIR}/SDL_mixer"
    EXCLUDE_FROM_ALL
)

file(GLOB C_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

if(ANDROID)
    add_library(main SHARED ${C_SOURCES})
    set(APP_TARGET main)
else()
    add_executable(${PROJECT_NAME} ${C_SOURCES})
    set(APP_TARGET ${PROJECT_NAME})
endif()

target_include_directories(${APP_TARGET}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(${APP_TARGET}
    PRIVATE
        SDL3_mixer::SDL3_mixer
        SDL3::SDL3
)

if(NOT ANDROID)
    install(
        TARGETS ${APP_TARGET}
        DESTINATION lib
    )

    install(
        DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/"
        DESTINATION "include/${PROJECT_NAME}"
    )
endif()
