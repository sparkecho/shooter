files = main.cpp fps_camera.h shader.h shader.cpp texture.h texture.cpp resource_manager.h resource_manager.cpp sprite_renderer.h sprite_renderer.cpp glad/src/glad.c stb_image.h stb_image.cpp

a.out : $(files)
	g++ $(files) -lglfw -lGL -lX11 -ldl -Iglad/include

.PHONY: clean
clean:
	rm -f *~ a.out
