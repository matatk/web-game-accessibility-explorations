.PHONY: run-native clean

main: menu.h menu.c main.c
	cc menu.c main.c -o main

run-native: main
	@./main

clean:
	-rm main
