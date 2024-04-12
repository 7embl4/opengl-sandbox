set(TARGET debuger)

add_library(${TARGET} INTERFACE)

target_include_directories(${TARGET} INTERFACE 
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/3rdparty/glew/include
)

target_link_libraries(${TARGET} INTERFACE 
	OpenGL::GL 
	libglew_static 
)