# ASCII-Engine
## Tiny engine and C11 library for terminal graphics 
### Used EGA for graphics, 8x8 EGA font on 80x43 screen. Used 16 colors from [EGA palette](https://en.wikipedia.org/wiki/Enhanced_Graphics_Adapter#:~:text=Default%20EGA%2016%2Dcolor%20palette%2C%20matching%20CGA%20colors).
![screenshot](https://github.com/Ztry8/ASCII-Engine/blob/main/screenshots/1.PNG)

Engine is based on SDL2.    
You need to copy the `core.c` and `core.h` files to your working directory and then link project with SDL2.   
Written in Visual C11. Example code of main file:
```
#include "core.h"

unsigned char init_game() { return 0; }

void input_game(SDL_Scancode key) {}

void update_core(struct Core* core) {
	set_tile(core, '@', INDEX_BRIGHT_YELLOW, 2, 0);
}

void shutdown_game() {}

int main(int argc, char* args[]) {
	struct Core core;
	if (init_core(&core) != 0) return 1;
	else run_core(&core);
	shutdown_core(&core);
	return 0;
}
```

### TODO:
- [x] Change color system
- [ ] Change screenshot
