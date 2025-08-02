cmake_minimum_required(VERSION 3.25)
project(OpenGL)

set(CMAKE_CXX_STANDARD 20)

# Collect all .cpp files in src/
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*)

# Add executable
add_executable(OpenGL ${SRC_FILES})

# Include path
target_include_directories(OpenGL PRIVATE ${CMAKE_SOURCE_DIR}/lib/include)


# Platform-specific linking
if (MSVC)
    # MSVC uses .lib
    target_link_libraries(OpenGL PRIVATE ${CMAKE_SOURCE_DIR}/lib/bin/libglfw3.lib)
    target_link_libraries(OpenGL PRIVATE opengl32)
elseif(MINGW)
    # MinGW uses .a
    target_link_libraries(OpenGL PRIVATE ${CMAKE_SOURCE_DIR}/lib/bin/libglfw3.a)
    target_link_libraries(OpenGL PRIVATE opengl32 gdi32)
elseif(UNIX)
    # Linux/Clang/GCC
    target_link_libraries(OpenGL PRIVATE ${CMAKE_SOURCE_DIR}/lib/bin/libglfw3.a)
    target_link_libraries(OpenGL PRIVATE dl m pthread X11)
endif()
