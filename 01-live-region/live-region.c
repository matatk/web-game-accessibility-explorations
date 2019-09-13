#include <stdio.h>
#include <time.h>

const int NUM_MESSAGES = 10;

#ifdef __EMSCRIPTEN__
extern void screen_reader_setup(void);
extern void screen_reader_announce(const char *);
#endif

int main() {
	printf("Starting up: hello, world!\n");

#ifdef __EMSCRIPTEN__
	screen_reader_setup();
#else
	printf("Not running via Emscripten, so not interfacing with screen-reader.\n");
#endif

	struct timespec pause;
	pause.tv_sec = 1;
	pause.tv_nsec = 0;

	printf("Going to print %d messages...\n", NUM_MESSAGES);

	for (int i = 0; i < NUM_MESSAGES; i++) {
		nanosleep(&pause, NULL);
		char *message;
		asprintf(&message, "This is message %d of %d.\n", i + 1, NUM_MESSAGES);
		printf("%s", message);
#ifdef __EMSCRIPTEN__
		screen_reader_announce(message);
#endif
	}

	return 0;
}
