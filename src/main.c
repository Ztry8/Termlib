#define SHOW_FPS
#include "core.h"

void input_game(SDL_Scancode key) {}

void update_game(renderer* renderer) {
	for (unsigned char i = 0; i < 255; i++) {
		draw_tile(renderer, i, BRIGHT_YELLOW, 15 + i%16, i/16);
	}

	print(renderer, "Hello World!", BLUE, 0, 0);
	print(renderer, "Hello World!", GREEN, 0, 1);
	print(renderer, "Hello World!", CYAN, 0, 2);
	print(renderer, "Hello World!", RED, 0, 3);
	print(renderer, "Hello World!", MAGENTA, 0, 4);
	print(renderer, "Hello World!", BROWN, 0, 5);
}

void shutdown_game() {}

int main(int argc, char* args[]) {
	renderer core;
	if (init_renderer(&core, 0, 2, "MyGame")) return 1;
	run_render(&core);
	shutdown_renderer(&core);
	return 0;
}