.PHONY: build-all run-native clean

UNIVERSAL_DEPS :=  menu/menu.h menu/menu_p.h menu/menu.c render/render.h

CLI_COMMON_DEPS := $(UNIVERSAL_DEPS) cli.c
CLI_COMMON_CODE := menu/menu.c cli.c

build-all: cli cli-fancy

cli: $(CLI_COMMON_DEPS) render/render_print.c
	cc $(CLI_COMMON_CODE) render/render_print.c -o $@

cli-fancy: $(CLI_COMMON_DEPS) render/render_print_fancy.c
	cc $(CLI_COMMON_CODE) render/render_print_fancy.c -o $@

run-native: cli cli-fancy
	./cli
	./cli-fancy

clean:
	-rm cli cli-fancy
