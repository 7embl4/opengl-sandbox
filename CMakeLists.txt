cmake_minimum_required (VERSION 3.8)
project ("opengl-sandbox")
set(CMAKE_CXX_STANDARD 17)

# setting up opengl
find_package(OpenGL REQUIRED)

# sub dependencies
add_subdirectory(glfw)
add_subdirectory(glew-cmake)
add_subdirectory(glm)

add_executable (opengl-sandbox "opengl-sandbox.cpp" "renderer.cpp" "renderer.h" "vertex_buffer.h" "vertex_buffer.cpp" "index_buffer.cpp" "index_buffer.h" "vertex_array.h" "vertex_array.cpp" "vertex_buffer_layout.h" "shader.h" "shader.cpp" "texture.h" "texture.cpp")
target_include_directories(opengl-sandbox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)
target_include_directories(opengl-sandbox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glew-cmake/include)
target_include_directories(opengl-sandbox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glm)

target_link_libraries(opengl-sandbox OpenGL::GL glfw libglew_static glm)
