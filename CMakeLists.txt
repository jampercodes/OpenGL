cmake_minimum_required(VERSION 3.25)
project(OpenGL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)


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
if(UNIX)
  # Copy it to the source directory
  add_custom_command(
      TARGET ${PROJECT_NAME}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
          ${CMAKE_BINARY_DIR}/compile_commands.json
          ${CMAKE_SOURCE_DIR}/compile_commands.json
      COMMENT "Copying compile_commands.json to project root"
  )
endif()
