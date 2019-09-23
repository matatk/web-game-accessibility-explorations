#include <stdio.h>
#include <time.h>

const int NUM_MESSAGES = 5;

#ifdef __EMSCRIPTEN__
#include <emscripten.h>

// Our custom JavaScript library functions
extern void screen_reader_setup(void);
extern void screen_reader_announce(const char *);
#endif

int main() {
	printf("Starting up: hello, world!\n");

#ifdef __EMSCRIPTEN__
	screen_reader_setup();
#else
	printf("Not running via Emscripten, so not interfacing with screen-reader.\n");

	struct timespec pause;
	pause.tv_sec = 2;
	pause.tv_nsec = 0;
#endif

	printf("Going to print %d messages...\n", NUM_MESSAGES);

	for (int i = 0; i < NUM_MESSAGES; i++) {
#ifdef __EMSCRIPTEN__
		emscripten_sleep(2000);
#else
		nanosleep(&pause, NULL);
#endif
		char *message;
		asprintf(&message, "This is message %d of %d.\n", i + 1, NUM_MESSAGES);
		printf("%s", message);
#ifdef __EMSCRIPTEN__
		screen_reader_announce(message);
#endif
	}

	return 0;
}
