cmake_minimum_required(VERSION 3.28)
project(spaceships)

option(DEBUG "Enable debugging" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(RESOURCE_DIR "${CMAKE_SOURCE_DIR}/res")
set(OUTPUT_RESOURCE_DIR "${CMAKE_BINARY_DIR}/res")

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${RESOURCE_DIR}
        ${OUTPUT_RESOURCE_DIR}
)

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC_FILES})

file(GLOB_RECURSE SUBDIRS LIST_DIRECTORIES true src/*)

set(INCLUDE_DIRS "")
foreach(dir ${SUBDIRS})
    if(IS_DIRECTORY "${dir}")
        list(APPEND INCLUDE_DIRS "${dir}")
    endif()
endforeach()
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS} src dependencies/cat/include)

find_library(CAT_LIB cat
    PATHS "${CMAKE_SOURCE_DIR}/dependencies/cat"
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${CAT_LIB})

if(DEBUG)
	target_compile_options(${PROJECT_NAME} PRIVATE -g)
	target_link_options(${PROJECT_NAME} PRIVATE -rdynamic)
endif()