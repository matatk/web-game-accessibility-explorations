.PHONY: build serve clean

build: emtestsdl1 emtestsdl1.html emtestsdl2 emtestsdl2.html

emtestsdl1: emtestsdl1.cpp
	g++ $< `sdl-config --cflags --libs` -o $@

emtestsdl2: emtestsdl2.cpp
	g++ $< `sdl2-config --cflags --libs` -o $@

emtestsdl1.html: emtestsdl1.cpp
	emcc $< -o $@

emtestsdl2.html: emtestsdl2.cpp
	emcc -s USE_SDL=2 $< -o $@

serve: build
	@echo 'serving on http://0.0.0.0:8080/'
	@python -m SimpleHTTPServer 8080

clean:
	-rm -v emtestsdl* emtestsdl*.js emtestsdl*.wasm emtestsdl*.html
