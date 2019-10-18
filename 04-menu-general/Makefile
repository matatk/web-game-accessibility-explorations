.PHONY: build-all test clean install-deps

CFLAGS += -fms-extensions -Wno-microsoft-anon-tag

ifeq ($(shell uname -s), Darwin)
SYS := -isystem /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/
endif

WIDGET_H := widget.h widgetbutton.h widgetsubpage.h widgetcontainer.h widgetlabel.h widgettextbox.h
WIDGET_C := widget.c widgetbutton.c widgetsubpage.c widgetcontainer.c widgetlabel.c widgettextbox.c

STD_H := page.h ui.h render.h
STD_C := main.c page.c  # UI and rendering are target-specific

CLI_C :=       ui_cli.c render_print.c
CLI_FANCY_C := ui_cli.c render_print_fancy.c

SDL_C :=       ui_sdl.c render_sdl.c render_accessibility.c
SDL_WEB :=     *library.js *html

build-all: page-cli page-cli-fancy page-sdl page-sdl.js

test:
	oclint-json-compilation-database

page-cli: $(STD_H) $(STD_C) $(WIDGET_H) $(WIDGET_C) $(CLI_C)
	$(CC) $(CFLAGS) $(SYS) $(STD_C) $(WIDGET_C) $(CLI_C) -o $@

page-cli-fancy: $(STD_H) $(STD_C) $(WIDGET_H) $(WIDGET_C) $(CLI_FANCY_C)
	$(CC) $(CFLAGS) $(SYS) $(STD_C) $(WIDGET_C) $(CLI_FANCY_C) -o $@

page-sdl: $(STD_H) $(STD_C) $(WIDGET_H) $(WIDGET_C) $(SDL_C) $(SDL_WEB)
	$(CC) $(CFLAGS) $(SYS) $(STD_C) $(WIDGET_C) $(SDL_C) \
		`sdl-config --cflags --libs` -lSDL_ttf -o $@

page-sdl.js: $(STD_H) $(STD_C) $(WIDGET_H) $(WIDGET_C) $(SDL_C) $(SDL_WEB)
	emcc $(CFLAGS) $(STD_C) $(WIDGET_C) $(SDL_C) \
		--js-library accessibility.library.js -o $@

serve: page-sdl.js
	@echo 'serving on http://0.0.0.0:8080/page-sdl.html'
	@python -m SimpleHTTPServer 8080

clean:
	-rm \
		page-cli \
		page-cli-fancy \
		page-sdl page-sdl.js page-sdl.wasm

install-deps:
	[ $$(uname -s) = 'Darwin' ] && brew install sdl sdl_ttf || sudo apt-get install libsdl1.2-dev libsdl-ttf2.0-dev
