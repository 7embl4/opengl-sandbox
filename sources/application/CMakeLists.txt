set(TARGET application)

add_executable(opengl-sandbox "opengl-sandbox.cpp")

target_include_directories(opengl-sandbox PUBLIC
	${CMAKE_SOURCE_DIR}/3rdparty/glfw/include
	${CMAKE_SOURCE_DIR}/3rdparty/glew/include
	${CMAKE_SOURCE_DIR}/3rdparty/glm
	#${CMAKE_SOURCE_DIR}/sources/renderer_core
	#${CMAKE_SOURCE_DIR}/sources/shader_compiler
	#${CMAKE_SOURCE_DIR}/sources/texture_compiler
)
target_link_libraries(opengl-sandbox PUBLIC 
	renderer_core 
	shader_compiler 
	texture_compiler

	OpenGL::GL 
	glfw 
	libglew_static 
	glm
)