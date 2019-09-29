.PHONY: all run build clean

all: build run

build: hello hello.js

hello: hello.c
	cc $< -o $@

hello.js: hello.c
	emcc $< -o $@

run: build
	@echo '--- Native C version ---'
	@./hello
	@echo
	@echo '--- WebAssembly version ---'
	@node hello.js

clean:
	-rm -v hello hello.js hello.wasm
