cmake_minimum_required (VERSION 2.6)

project (DCMakeDemo)

add_executable(DCMakeDemo DCMakeDemo.cpp)

if(MINGW)
	target_include_directories(DCMakeDemo PUBLIC
		C:/workspaces/sdl/mingw/SDL2-2.0.6/x86_64-w64-mingw32/include
		C:/workspaces/sdl/mingw/SDL2-2.0.6/x86_64-w64-mingw32/include/SDL2
		C:/workspaces/sdl/mingw/SDL2_image-2.0.1/x86_64-w64-mingw32/include
	)
	target_link_libraries(DCMakeDemo
		-LC:/workspaces/sdl/mingw/SDL2-2.0.6/x86_64-w64-mingw32/lib
		-LC:/workspaces/sdl/mingw/SDL2_image-2.0.1/x86_64-w64-mingw32/lib
		mingw32
		SDL2main
		SDL2
		SDL2_image
	)
elseif(QNXNTO)
	target_include_directories(DCMakeDemo PUBLIC
		C:/workspaces/sdl/qnx/include
		C:/workspaces/sdl/qnx/include/SDL2
	)
	target_link_libraries(DCMakeDemo
		-LC:/workspaces/sdl/qnx/lib
		SDL2main
		SDL2
		SDL2_image
	)
elseif(WASM)
	set(CMAKE_EXECUTABLE_SUFFIX ".html")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS=\"[\"\"png\"\"]\"")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS=\"[\"\"png\"\"]\"")
	target_link_libraries(DCMakeDemo "--preload-file ${CMAKE_SOURCE_DIR}/assets/owl.png@owl.png" --emrun)
endif()
