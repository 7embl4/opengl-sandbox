cmake_minimum_required (VERSION 3.8)
project ("opengl-sandbox")
set(CMAKE_CXX_STANDARD 17)

# setting up opengl
find_package(OpenGL REQUIRED)

# sub dependencies
add_subdirectory(3rdparty/glfw)
add_subdirectory(3rdparty/glew)
add_subdirectory(3rdparty/glm)

# libs
add_subdirectory(sources/debuger)
add_subdirectory(sources/renderer_core)
add_subdirectory(sources/shader_compiler)
add_subdirectory(sources/texture_compiler)
add_subdirectory(sources/application)
