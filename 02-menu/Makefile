.PHONY: build-all clean

UNIVERSAL_DEPS := menu/menu.h menu/menu_p.h menu/menu.c render/render.h

CLI_COMMON_DEPS := $(UNIVERSAL_DEPS) cli.c
CLI_COMMON_CODE := menu/menu.c cli.c

GUI_AND_ACCESSIBILITY_RENDERERS := \
	render/render_sdl.c render/render_accessibility.c
GUI_AND_ACCESSIBILITY_DEPS := \
	$(GUI_AND_ACCESSIBILITY_RENDERERS)  # not accessibility.library.js

build-all: cli cli-fancy sdl sdl.html

cli: $(CLI_COMMON_DEPS) render/render_print.c
	cc $(CLI_COMMON_CODE) render/render_print.c -o $@

cli-fancy: $(CLI_COMMON_DEPS) render/render_print_fancy.c
	cc $(CLI_COMMON_CODE) render/render_print_fancy.c -o $@

sdl: sdl.c $(UNIVERSAL_DEPS) $(GUI_AND_ACCESSIBILITY_DEPS)
	cc menu/menu.c $(GUI_AND_ACCESSIBILITY_RENDERERS) sdl.c \
		`sdl-config --cflags --libs` -lSDL_ttf -o $@

sdl.html: sdl.c $(UNIVERSAL_DEPS) $(GUI_AND_ACCESSIBILITY_DEPS)
	emcc menu/menu.c $(GUI_AND_ACCESSIBILITY_RENDERERS) sdl.c \
		--js-library accessibility.library.js -o $@

serve: sdl.html
	@echo 'serving on http://0.0.0.0:8080/$<'
	@python -m SimpleHTTPServer 8080

clean:
	-rm cli cli-fancy sdl sdl.js sdl.wasm sdl.html
