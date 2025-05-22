cmake_minimum_required(VERSION 3.11)
project(Paradox-Editor)

# Edit this as required by your build or change FLTK_COMMIT in the
# CMake cache (e.g. with cmake-gui)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

include(FetchContent)

set(FLTK_BUILD_TEST OFF CACHE BOOL " " FORCE)
if(UNIX AND NOT APPLE) 
    set(OPTION_USE_PANGO ON CACHE BOOL " " FORCE)
endif()

FetchContent_Declare(FLTK
    GIT_REPOSITORY      https://github.com/fltk/fltk
)

FetchContent_MakeAvailable(FLTK)

    # ${CMAKE_SOURCE_DIR}/src/Editor/Window.cpp
    # ${CMAKE_SOURCE_DIR}/src/Editor/TextEditor.cpp    
    # ${CMAKE_SOURCE_DIR}/src/main.cpp

file(GLOB SRC
    ${PROJECT_SOURCE_DIR}/src/Common/*.cpp
    ${PROJECT_SOURCE_DIR}/src/Editor/*.cpp
    ${PROJECT_SOURCE_DIR}/src/Lexer/*.cpp
)

message("SOURCES ${SRC}")


add_executable(Paradox-Editor ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${SRC}
)

target_include_directories(Paradox-Editor PRIVATE 
    ${fltk_BINARY_DIR} 
    ${fltk_SOURCE_DIR} 
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(Paradox-Editor PRIVATE fltk) # + fltk_gl fltk_images fltk_png fltk_jpeg fltk_z 

if(APPLE)
    target_link_libraries(Paradox-Editor PRIVATE "-framework Cocoa") # needed for macOS
endif()

