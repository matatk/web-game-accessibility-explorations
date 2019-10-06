.PHONY: build-all run-native serve clean

build-all: live-region live-region.html

live-region: live-region.c
	cc $< -o $@

live-region.html: live-region.c live-region.library.js
	emcc $< -s ASYNCIFY -O3 -o $@ --js-library live-region.library.js

run-native: live-region
	@./live-region

serve: live-region.html
	@echo 'serving on http://0.0.0.0:8080/live-region.html'
	@python -m SimpleHTTPServer 8080

clean:
	-rm -v live-region live-region.js live-region.wasm live-region.html
