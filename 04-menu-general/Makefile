.PHONY: build-all clean install-deps

build-all: menu-cli menu-cli-fancy menu-sdl menu-sdl.js

menu-cli: *h *c *library.js *html
	cc main.c menu.c gui_cli.c render_print.c -o $@

menu-cli-fancy: *h *c *library.js *html
	cc main.c menu.c gui_cli.c render_print_fancy.c -o $@

menu-sdl: *h *c *library.js *html
	cc main.c menu.c gui_sdl.c render_sdl.c render_accessibility.c \
		`sdl-config --cflags --libs` -lSDL_ttf -o $@

menu-sdl.js: *h *c *library.js *html
	emcc main.c menu.c gui_sdl.c render_sdl.c render_accessibility.c \
		--js-library accessibility.library.js -o $@

serve: menu-sdl.js
	@echo 'serving on http://0.0.0.0:8080/menu-sdl.html'
	@python -m SimpleHTTPServer 8080

clean:
	-rm \
		menu-cli \
		menu-cli-fancy \
		menu-sdl menu-sdl.js menu-sdl.wasm

install-deps:
	[ $$(uname -s) = 'Darwin' ] && brew install sdl sdl_ttf || sudo apt-get install libsdl1.2-dev libsdl-ttf2.0-dev
