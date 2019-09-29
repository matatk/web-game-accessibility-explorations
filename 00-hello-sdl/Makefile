.PHONY: build serve clean

build: hello-sdl1 hello-sdl1.html hello-sdl2 hello-sdl2.html

hello-sdl1: hello-sdl1.c
	cc $< `sdl-config --cflags --libs` -o $@

hello-sdl2: hello-sdl2.c
	cc $< `sdl2-config --cflags --libs` -o $@

hello-sdl1.html: hello-sdl1.c
	emcc $< -o $@

hello-sdl2.html: hello-sdl2.c
	emcc -s USE_SDL=2 $< -o $@

serve: build
	@echo 'serving on http://0.0.0.0:8080/'
	@python -m SimpleHTTPServer 8080

clean:
	-rm -v hello-sdl1 hello-sdl2 hello-sdl*.js hello-sdl*.wasm hello-sdl*.html
