.PHONY: build-all run-native run-native-fancy clean

UNIVERSAL_DEPS :=  menu/menu.h menu/menu_p.h menu/menu.c render/render.h

build-all: cli cli-fancy

cli: $(UNIVERSAL_DEPS) render/render_print.c cli.c
	cc menu/menu.c render/render_print.c cli.c -o $@

cli-fancy: $(UNIVERSAL_DEPS) render/render_print_fancy.c cli.c
	cc menu/menu.c render/render_print_fancy.c cli.c -o $@

run-native: cli
	@./cli

run-native-fancy: cli-fancy
	@./cli-fancy

clean:
	-rm cli cli-fancy
