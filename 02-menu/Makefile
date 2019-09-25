.PHONY: run-native clean

UNIVERSAL_DEPS :=  menu/menu.h menu/menu_p.h menu/menu.c render/render.h

cli: $(UNIVERSAL_DEPS) render/render_print.c cli.c
	cc menu/menu.c render/render_print.c cli.c -o cli

run-native: cli
	@./cli

clean:
	-rm cli
