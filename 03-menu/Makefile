.PHONY: build-all clean install-deps

UNIVERSAL_DEPS := menu/menu.h menu/menu_p.h menu/menu.c render/render.h

CLI_COMMON_DEPS := $(UNIVERSAL_DEPS) main-cli.c
CLI_COMMON_CODE := menu/menu.c main-cli.c

GUI_AND_ACCESSIBILITY_RENDERERS := \
	render/render_sdl.c render/render_accessibility.c
GUI_AND_ACCESSIBILITY_DEPS := \
	$(GUI_AND_ACCESSIBILITY_RENDERERS) accessibility.library.js

build-all: menu-cli menu-cli-fancy menu-sdl menu-sdl.js

menu-cli: $(CLI_COMMON_DEPS) render/render_print.c
	cc $(CLI_COMMON_CODE) render/render_print.c -o $@

menu-cli-fancy: $(CLI_COMMON_DEPS) render/render_print_fancy.c
	cc $(CLI_COMMON_CODE) render/render_print_fancy.c -o $@

menu-sdl: main-sdl.c $(UNIVERSAL_DEPS) $(GUI_AND_ACCESSIBILITY_DEPS)
	cc menu/menu.c $(GUI_AND_ACCESSIBILITY_RENDERERS) main-sdl.c \
		`sdl-config --cflags --libs` -lSDL_ttf -o $@

menu-sdl.js: main-sdl.c $(UNIVERSAL_DEPS) $(GUI_AND_ACCESSIBILITY_DEPS)
	emcc menu/menu.c $(GUI_AND_ACCESSIBILITY_RENDERERS) main-sdl.c \
		--js-library accessibility.library.js -o $@

serve: menu-sdl.js
	@echo 'serving on http://0.0.0.0:8080/menu-sdl.html'
	@python -m SimpleHTTPServer 8080

clean:
	-rm menu-cli menu-cli-fancy menu-sdl menu-sdl.js menu-sdl.wasm

install-deps:
	[ $$(uname -s) = 'Darwin' ] && brew install sdl sdl_ttf || sudo apt-get install libsdl1.2-dev libsdl-ttf2.0-dev
