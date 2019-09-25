.PHONY: build-all run-native clean

UNIVERSAL_DEPS :=  menu/menu.h menu/menu_p.h menu/menu.c render/render.h

CLI_COMMON_DEPS := $(UNIVERSAL_DEPS) cli.c
CLI_COMMON_CODE := menu/menu.c cli.c

build-all: cli cli-fancy sdl sdl.html

cli: $(CLI_COMMON_DEPS) render/render_print.c
	cc $(CLI_COMMON_CODE) render/render_print.c -o $@

cli-fancy: $(CLI_COMMON_DEPS) render/render_print_fancy.c
	cc $(CLI_COMMON_CODE) render/render_print_fancy.c -o $@

sdl: sdl.c $(UNIVERSAL_DEPS) render/render_print.c
	cc `sdl-config --cflags --libs` \
		menu/menu.c render/render_print.c sdl.c -o $@

sdl.html: sdl.c $(UNIVERSAL_DEPS) render/render_print.c
	emcc menu/menu.c render/render_print.c sdl.c -o $@

serve: sdl.html
	@echo 'serving on http://0.0.0.0:8080/$<'
	@python -m SimpleHTTPServer 8080

run-native: cli cli-fancy
	./cli
	./cli-fancy

clean:
	-rm cli cli-fancy
