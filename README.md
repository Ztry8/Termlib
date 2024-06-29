# ASCII-Engine
## Tiny C99 library with only one header for EGA terminal graphics
### Used EGA for graphics, 8x8 EGA font on 80x43 screen. Used 16 colors from [EGA palette](https://en.wikipedia.org/wiki/Enhanced_Graphics_Adapter#Color_palette).
![screenshot](https://github.com/Ztry8/ASCII-Engine/blob/main/screenshots/1.PNG)

#### Linking
Engine is based on SDL2.    
You just need to copy the `core.h` file to your working directory and then link project with SDL2.   

#### About engine
##### Please don't change the `#define` directives in `core.h`. This could disrupt the engine's logic!
The engine uses batching for rendering tiles, but tile culling has not been implemented yet. See the TODO list.   
The window closes when you press the Esc key, but not when you press Alt+F4 (this only works on Windows).
It has vsync only as a frame rate cap and display fps on window's title, graphics API provided by SDL2. The font used for graphics is built into the header code.
It doesn't have a feature for mouse support, and it isn't planned to be added in the future.

#### Using
Define `VSYNC` before including header for v-sync.   
Define the `SCALE` as a number to set the correct scale for your graphics.   
`SCALE` = 1: 640x344 resolution,   
`SCALE` = 2: 1280x688 resolution, etc.

Firstly, include the header file. Then, write the functions:   
`init_game()` used to start your game. It helps you create levels or do anything else you need.   
`input_game(SDL_Scancode key)` used for processing player's input, see [SDL_Scancode](https://wiki.libsdl.org/SDL2/SDL_Scancode)   
`update_game(struct Core* core)` used for processing graphics and is called every frame.   
`shutdown_game()` used for free up resources in your game.   

Called function:   
`set_tile(struct Core*, char, unsigned char, long, long)` used for displaying and drawing tiles.   
The second argument is a character to draw. Use a character enclosed in single quotes, not a number code!   
The third argument is color. You can also look at the names in the header.   
The fourth and fifth arguments are the x and y coordinates.

In the main files, you need to create and initialize the `Core` using the `init_core()` function, which takes a `struct Core*`, `vsync`, `scale` as an arguments.  
Then, activate and run the `Core` using the `run_core(struct Core*)` function.   
Finally, release and free the `Core` by using the `shutdown_core(struct Core*)` function.

Example code of main file:
```
//#define VSYNC
#define SCALE 2
#include "core.h"

unsigned char init_game() { return 0; }

void input_game(SDL_Scancode key) {}

void update_game(struct Core* core) {
	set_tile(core, '@', INDEX_BRIGHT_YELLOW, 2, 0);
}

void shutdown_game() {}

int main(int argc, char* args[]) {
	struct Core core;
	if (init_core(&core, 0, 2) != 0) return 1;
	else run_core(&core);
	shutdown_core(&core);
	return 0;
}
```

### TODO:
- [ ] Change the colour system to make it more user-friendly and efficient.
- [ ] Add tile culling.
- [ ] Perhaps, add support for sound.
