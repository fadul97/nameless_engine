project(NamelessEngine)

add_executable(NamelessEngine main.cpp gl.c error_list.c window_x11.cpp context_gl.cpp input_x11.cpp engine.cpp app.cpp renderer_x11.cpp test_app.cpp)

if(UNIX)
	target_link_libraries(NamelessEngine -lX11 -lGL)
endif()