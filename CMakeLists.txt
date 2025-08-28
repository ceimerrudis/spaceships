cmake_minimum_required(VERSION 3.50)
project(spaceships)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/res")
set(OUTPUT_RESOURCE_DIR "${CMAKE_BINARY_DIR}/res")

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${RESOURCE_DIR}
        ${OUTPUT_RESOURCE_DIR}
)

set(FT_DISABLE_HARFBUZZ ON CACHE BOOL "Disable HarfBuzz")
add_subdirectory(dependencies/freetype-2.13.3)

add_subdirectory(dependencies/glfw-3.4)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries only" FORCE)

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

add_library(glad dependencies/glad/src/glad.c)


file(GLOB_RECURSE SUBDIRS LIST_DIRECTORIES true src/*)

set(INCLUDE_DIRS "")
foreach(dir ${SUBDIRS})
    if(IS_DIRECTORY "${dir}")
        list(APPEND INCLUDE_DIRS "${dir}")
    endif()
endforeach()
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE src/)
target_include_directories(${PROJECT_NAME} PRIVATE dependencies/freetype-2.13.3/include)
target_include_directories(${PROJECT_NAME} PRIVATE dependencies/glfw-3.4/include/GLFW)
target_include_directories(${PROJECT_NAME} PRIVATE dependencies/stb_image)
target_include_directories(glad PUBLIC dependencies/glad/include)

target_link_libraries(${PROJECT_NAME} glfw glad OpenGL32 freetype ws2_32 winmm)