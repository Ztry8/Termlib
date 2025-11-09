#define SHOW_FPS
#include "core.h"

wav_sound *drink;

void keyboard_game(SDL_Scancode key, renderer* renderer) {
	if (key == SDL_SCANCODE_E) play_wav(drink, renderer);
}

void mouse_game(renderer* renderer, signed x, signed y, char button) {
	if (button == 0) draw_tile(renderer, '@', BRIGHT_YELLOW, x, y);
	else draw_tile(renderer, '@', MAGENTA, x, y);
}

void update_game(renderer* renderer, float frame_time) {
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

int main() {
	renderer core;
	if (init_renderer(&core, 1, 2, "MyGame")) return 1;

	drink = load_wav("../assets/drink.wav", &core);

	run_render(&core);
	shutdown_renderer(&core);
	return 0;
}
