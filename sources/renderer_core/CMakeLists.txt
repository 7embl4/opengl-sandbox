set(TARGET renderer_core)

add_library(${TARGET} INTERFACE)

target_include_directories(${TARGET} INTERFACE 
	${CMAKE_CURRENT_SOURCE_DIR} 
	${CMAKE_SOURCE_DIR}/3rdparty/glfw/include
	${CMAKE_SOURCE_DIR}/3rdparty/glew/include
	${CMAKE_SOURCE_DIR}/3rdparty/glm
	${CMAKE_SOURCE_DIR}/3rdparty/stb
	${CMAKE_SOURCE_DIR}/sources/shader_compiler
	${CMAKE_SOURCE_DIR}/sources/debuger
)

target_link_libraries(${TARGET} INTERFACE shader_compiler debuger)
target_link_libraries(${TARGET} INTERFACE OpenGL::GL glfw libglew_static glm)
