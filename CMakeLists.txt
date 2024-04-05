cmake_minimum_required (VERSION 3.8)
project ("opengl-sandbox")
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/path/to/your/makefiles")

# setting up opengl
find_package(OpenGL REQUIRED)

# sub dependencies
add_subdirectory(glfw)
add_subdirectory(glew-cmake)

add_executable (opengl-sandbox "opengl-sandbox.cpp")
target_include_directories(opengl-sandbox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include)
target_include_directories(opengl-sandbox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glew-cmake/include)

target_link_libraries(opengl-sandbox OpenGL::GL glfw libglew_static)
