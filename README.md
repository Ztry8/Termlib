# ASCII-Engine
## Tiny C99 library with only one header for [EGA](https://en.wikipedia.org/wiki/Enhanced_Graphics_Adapter) terminal graphics
![screenshot](https://github.com/Ztry8/ASCII-Engine/blob/main/screenshots/3.png)


### About engine

#### Font
The engine uses 8x8 EGA font on 80x43 screen. Used 16 colors from [default EGA palette](https://en.wikipedia.org/wiki/Enhanced_Graphics_Adapter#Color_palette).  
The font used for graphics is built into the header code.

#### Rendering
The engine uses batching for rendering tiles and tile culling has been implemented, it has vsync only as a frame rate cap. 
The graphics API provided by SDL2. 

#### Input
The engine uses the keyboard as input, and does not have mouse support, and there are no plans to add it in the future.

#### Does it support C++ ?
Yes, the library has been tested with C++ and works pretty well.


### Linking

#### Windows
Engine is based on SDL2.    
You just need to copy the `src/core.h` file to your working directory and then link project with SDL2.   

#### Linux
Make sure you have `git`, `cmake`, `ninja` or `make`, `sdl2-dev-package` installed.
```
git clone https://github.com/Ztry8/ASCII-Engine.git
touch src/main.c
# put some code in the file `src/main.c`, see `Using`
mkdir build/
cd build/
```
For  `make`:
```
cmake ../src
make
```
For  `ninja`:
```
cmake ../src -G Ninja
ninja
```
After that, you can see your application as `build/ASCII-Engine`.


### Using

#### Example
```
//#define SHOW_FPS
#include "core.h"

unsigned char init_game() { return 0; }

void input_game(SDL_Scancode key) {}

void update_game(struct Core* core) {
	for (unsigned char i = 0; i < 255; i++) {
		draw_tile(core, i, BRIGHT_YELLOW, 15 + i%16, i/16);
	}

	print(core, "Hello World!", BLUE, 0, 0);
	print(core, "Hello World!", GREEN, 0, 1);
	print(core, "Hello World!", CYAN, 0, 2);
	print(core, "Hello World!", RED, 0, 3);
	print(core, "Hello World!", MAGENTA, 0, 4);
	print(core, "Hello World!", BROWN, 0, 5);
}

void shutdown_game() {}

int main(int argc, char* args[]) {
	struct Core core;
	if (init_core(&core, 0, 2, "MyGame")) return 1;
	run_core(&core);
	shutdown_core(&core);
	return 0;
}
```
Result:
![screenshot](https://github.com/Ztry8/ASCII-Engine/blob/main/screenshots/example.png)
#### Run engine
Please don't change the `#define` directives in `core.h`. This could disrupt the engine's logic!
Define `SHOW_FPS` before including header for displaying fps instead of app name.  

In the main files, you need to create and initialize the `Core` using the `init_core()` function, which takes a `struct Core*`, `vsync`, `scale` as an arguments.   
`scale` = 1: 640x344 resolution,   
`scale` = 2: 1280x688 resolution, etc. 
Then, activate and run the `Core` using the `run_core(struct Core*)` function.   
Finally, release and free the `Core` by using the `shutdown_core(struct Core*)` function.

#### Functions

##### Callbacks:
`init_game()` used to start your game. It helps you create levels or do anything else you need.   
`input_game(SDL_Scancode key)` used for processing player's input, see [SDL_Scancode](https://wiki.libsdl.org/SDL2/SDL_Scancode)   
`update_game(struct Core* core)` used for processing graphics and is called every frame.   
`shutdown_game()` used for free up resources in your game.   

##### Called function:   
`draw_tile(struct Core*, char, unsigned char*, long, long)` used for displaying and drawing tiles.   
The second argument is a character to draw. Use a character enclosed in single quotes, not a number code!   
The third argument is color. You can also look at the names in the header.   
The fourth and fifth arguments are the x and y coordinates.   

`draw_tile_camera(struct Core*, char, unsigned char*, long, long, long, long)` used for displaying and drawing tiles relative to the center of the screen.   
The second argument is a character to draw. Use a character enclosed in single quotes, not a number code!   
The third argument is color. You can also look at the names in the header.   
The fourth and fifth arguments are the x and y coordinates.
The sixth and seventh arguments are the x and y coordinates of the camera.

`print(struct Core*, const char*, unsigned char*, long, long)` used for displaying text.   
The second argument is a text to display.    
The third argument is color. You can also look at the names in the header.   
The fourth and fifth arguments are the x and y coordinates.

### TODO
- [x] Added tile culling and camera support.
- [x] Added print function
- [ ] Perhaps, add support for sound.
