.PHONY: all run build clean

all: build run

build: emtest emtest.js

emtest: emtest.c
	cc $< -o $@

emtest.js: emtest.c
	emcc $< -o $@

run: build
	@echo '--- Native C version ---'
	@./emtest
	@echo
	@echo '--- WebAssembly version ---'
	@node emtest.js

clean:
	-rm -v emtest emtest.js emtest.wasm
