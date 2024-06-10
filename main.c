#pragma warning(disable: 4100)
#include "core.h"

unsigned char init_game() {
	return 0;
}

void input_game(SDL_Scancode key) {
	switch (key) {
	}
}

void update_core(struct Core* core) {
	set_tile(core, '#', INDEX_WHITE, 0, 0);
	set_tile(core, '.', INDEX_WHITE, 1, 0);
	set_tile(core, '@', INDEX_YELLOW, 2, 0);
	set_tile(core, '.', INDEX_WHITE, 3, 0);
	set_tile(core, '#', INDEX_WHITE, 4, 0);
}

void shutdown_game() {}

int main(int argc, char* args[]) {
	struct Core core;
	if (init_core(&core) != 0) return 1;
	else run_core(&core);
	shutdown_core(&core);
	return 0;
}