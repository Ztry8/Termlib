# Termlib
## Lightweight and simple C99 library with a single header for terminal graphics
![screenshot](https://github.com/Ztry8/ASCII-Engine/blob/main/screenshots/3.png)

### About library

#### Library Goals
The main goal of the library is to provide fast, easy, and efficient rendering.   

#### Font
The library uses 8x8 EGA font on 80x45 screen. Used 16 colors from [default EGA palette](https://en.wikipedia.org/wiki/Enhanced_Graphics_Adapter#Color_palette).  
The font used for graphics is built into the header code.

#### Rendering
The library uses batching for rendering tiles and tile culling has been implemented, it has vsync only as a frame rate cap. 
The graphics API provided by SDL2. 

#### Input
The library uses the keyboard as input, and there are plans to add a mouse support in the future.

#### Does it work with C++?
Yes, the library has been tested with C++ and works pretty well.


### Linking

#### Windows
Engine is based on SDL2.    
You just need to copy the `src/core.h` file to your working directory and then link project with SDL2.   

#### Linux
Make sure you have `git`, `cmake`, `ninja` or `make`, `sdl2-dev-package` installed.
```
git clone https://github.com/Ztry8/Termlib.git
mkdir build/
cd build/
```
For  `ninja` (Recommended):
```
cmake ../src -G Ninja
ninja
```
For  `make`:
```
cmake ../src
make
```
After that, you can see your application as `build/Termlib-App`.

### Usage

#### Example
```
//#define SHOW_FPS
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
```
Result:
![screenshot](https://github.com/Ztry8/ASCII-Engine/blob/main/screenshots/example.png)
#### Run engine
Define `SHOW_FPS` before including header for displaying fps instead of app name.  

In the main files, you need to create and initialize the `Core` using the `init_renderer()` function, which takes a `renderer*`, `vsync`, `scale` as an arguments.   
`scale` = 1: 640x344 resolution,   
`scale` = 2: 1280x688 resolution, etc. 
Then, activate and run the `renderer` using the `run_render(renderer*)` function.   
Finally, release and free the `renderer` by using the `shutdown_renderer(renderer*)` function.

#### Functions

##### Callbacks:
`input_game(SDL_Scancode key)` used for processing player's input, see [SDL_Scancode](https://wiki.libsdl.org/SDL2/SDL_Scancode)   
`update_game(renderer*)` used for processing graphics and is called every frame.   
`shutdown_game()` used for free up resources in your game.   

##### Called function:   
`draw_tile(renderer*, char, unsigned char*, long, long)` used for displaying and drawing tiles.   
The second argument is a character to draw. Use a character enclosed in single quotes, not a number code!   
The third argument is color. You can also look at the names in the header.   
The fourth and fifth arguments are the x and y coordinates.   

`draw_tile_camera(renderer*, char, unsigned char*, long, long, long, long)` used for displaying and drawing tiles relative to the center of the screen.   
The second argument is a character to draw. Use a character enclosed in single quotes, not a number code!   
The third argument is color. You can also look at the names in the header.   
The fourth and fifth arguments are the x and y coordinates.
The sixth and seventh arguments are the x and y coordinates of the camera.

`print(renderer*, const char*, unsigned char*, long, long)` used for displaying text.   
The second argument is a text to display.    
The third argument is color. You can also look at the names in the header.   
The fourth and fifth arguments are the x and y coordinates.

### TODO
- [x] Added tile culling and camera support.
- [x] Added print function.   
~~Add support for sound.~~
- [ ] Add mouse support
