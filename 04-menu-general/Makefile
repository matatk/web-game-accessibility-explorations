.PHONY: build-all clean install-deps

WIDGET_H := widget.h widgetbutton.h widgetsubmenu.h
WIDGET_C := widget.c widgetbutton.c widgetsubmenu.c

STD_H := menu.h ui.h render.h
STD_C := main.c menu.c  # UI and rendering are target-specific

CLI_C :=       ui_cli.c render_print.c
CLI_FANCY_C := ui_cli.c render_print_fancy.c

SDL_C :=       ui_sdl.c render_sdl.c render_accessibility.c
SDL_WEB :=     *library.js *html

build-all: menu-cli menu-cli-fancy menu-sdl menu-sdl.js

menu-cli: $(STD_H) $(STD_C) $(WIDGET_H) $(WIDGET_C) $(CLI_C)
	cc $(STD_C) $(WIDGET_C) $(CLI_C) -o $@

menu-cli-fancy: $(STD_H) $(STD_C) $(WIDGET_H) $(WIDGET_C) $(CLI_FANCY_C)
	cc $(STD_C) $(WIDGET_C) $(CLI_FANCY_C) -o $@

menu-sdl: $(STD_H) $(STD_C) $(WIDGET_H) $(WIDGET_C) $(SDL_C) $(SDL_WEB)
	cc $(STD_C) $(WIDGET_C) $(SDL_C) \
		`sdl-config --cflags --libs` -lSDL_ttf -o $@

menu-sdl.js: $(STD_H) $(STD_C) $(WIDGET_H) $(WIDGET_C) $(SDL_C) $(SDL_WEB)
	emcc $(STD_C) $(WIDGET_C) $(SDL_C) \
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
