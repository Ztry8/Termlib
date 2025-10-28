# Termlib
[![GitHub last commit](https://img.shields.io/github/last-commit/ztry8/termlib)](https://github.com/ztry8/termlib/commits)
[![License](https://img.shields.io/github/license/ztry8/termlib)](https://github.com/ztry8/termlib/blob/main/LICENSE)
## Lightweight and simple C/C++ library with a single header for terminal graphics written in C
![screenshot](https://github.com/Ztry8/ASCII-Engine/blob/main/assets/3.png)
![screenshot](https://github.com/Ztry8/ASCII-Engine/blob/main/assets/1.PNG)

### About library

#### Library Goals
The main goal of the library is to provide fast, easy, and efficient tool for rendering, playback and input proccesing.   
It was originally intended to be used to create [traditional roguelikes](https://roguebasin.com/index.php/Main_Page).

#### Font
The library uses 8x8 EGA font on 80x45 screen. Used 16 colors from [default EGA palette](https://en.wikipedia.org/wiki/Enhanced_Graphics_Adapter#Color_palette).  
The font used for graphics is built into the header code.

#### Rendering
The library uses batching for rendering tiles, tile culling has been implemented.   
The library has VSync only as a frame rate cap.   
The graphics API provided by SDL2 (opengl or direct2d, etc.)

#### Input
The library uses the keyboard as input, and there are plans to add a mouse support in the future.

#### Sounds
The library supports loading sounds from `.wav` files and playing them.

#### What platforms does the library work on?
I tested it on Windows 10, Debian 12, and macOS 10.13,   
and all functions worked correctly across these platforms.   
The library should be compatible with all platforms supported by SDL2.

#### Does it work with C++?
Yes, the library has been tested with C++ and works pretty well.


### Building

#### Windows
Engine is based on SDL2.    
You just need to copy the `src/core.h` file to your working directory and then link project with SDL2.   
[Perhaps this will help you](https://wiki.libsdl.org/SDL2/Installation#windows_xpvista7810)

#### Distributing your .exe
All necessary assets are built into your library's `core.h` file,   
and if you use sounds in your game, you'll also need to distribute them along with your executable file.   
If you have chosen the dynamic linking type with SDL2, place [this .dll for x86](https://github.com/libsdl-org/SDL/releases/download/release-2.32.10/SDL2-2.32.10-win32-x86.zip) or [this for x64](https://github.com/libsdl-org/SDL/releases/download/release-2.32.10/SDL2-2.32.10-win32-x64.zip) in the same folder with .exe

#### Linux/MacOs
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

#### Distributing your game for Linux/MacOs
If you compiled the game using the instructions above,   
the player just need install SDL2 on his system using the following commands:

Debian-based:
```bash
sudo apt update
sudo apt install libsdl2-2.0-0
```
RHEL-based:
```bash
sudo dnf check-update
sudo dnf install SDL2
```
Arch-based:
```bash
sudo pacman -Sy
sudo pacman -S sdl2
```
MacOs:
```bash
sudo port selfupdate
sudo port install libsdl2
```

and if you use sounds in your game, you'll also need to distribute them along with your executable file.   

### Usage

#### Example
```c
// #define SHOW_FPS
#include "core.h"

wav_sound *drink;

void input_game(SDL_Scancode key, renderer* renderer) {
	if (key == SDL_SCANCODE_E) play_wav(drink, renderer);
}

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

int main() {
	renderer core;
	if (init_renderer(&core, 0, 2, "MyGame")) return 1;

	drink = load_wav("../assets/drink.wav", &core);

	run_render(&core);
	shutdown_renderer(&core);
	return 0;
}
```
Result:
![screenshot](https://github.com/Ztry8/ASCII-Engine/blob/main/assets/example.png)
#### Run engine
Define `SHOW_FPS` before including header for displaying fps instead of app name.  

In the main files, you need to create and initialize the `Core` using the `init_renderer()` function, which takes a `renderer*`, `vsync`, `scale` as an arguments.   
`scale` = 1: 640x344 resolution,   
`scale` = 2: 1280x688 resolution, etc. 
Then, activate and run the `renderer` using the `run_render(renderer*)` function.   
Finally, release and free the `renderer` by using the `shutdown_renderer(renderer*)` function.

#### Functions

##### Callbacks:
```c
input_game(SDL_Scancode key, renderer* renderer)
```   
Used for processing player's input, see [SDL_Scancode](https://wiki.libsdl.org/SDL2/SDL_Scancode)   


```c
update_game(renderer*)
```  
Used for processing graphics and is called every frame.   


```c
shutdown_game()
```   
Used for free up resources in your game.   


##### Called function:   
```c
draw_tile(renderer*, char, unsigned char*, long, long)
```   
Used for displaying and drawing tiles.   
The second argument is a character to draw. Use a character enclosed in single quotes, not a number code!   
The third argument is color. You can also look at the names in the header.   
The fourth and fifth arguments are the x and y coordinates.   


```c
draw_tile_camera(renderer*, char, unsigned char*, long, long, long, long)
```   
Used for displaying and drawing tiles relative to the center of the screen.   
The second argument is a character to draw. Use a character enclosed in single quotes, not a number code!   
The third argument is color. You can also look at the names in the header.   
The fourth and fifth arguments are the x and y coordinates.
The sixth and seventh arguments are the x and y coordinates of the camera.


```c
print(renderer*, const char*, unsigned char*, long, long)
```   
used for displaying text.   
The second argument is a text to display.    
The third argument is color. You can also look at the names in the header.   
The fourth and fifth arguments are the x and y coordinates.

```c
load_wav(const char*, renderer*)
```   
used for loading sound in WAV format.
The first argument is a path to file.
Returns wav_sound*

```c
void play_wav(wav_sound*, renderer* core)
```   
used for playing sound in WAV format.
The first argument is a sound to play.

### TODO
- [x] Added tile culling and camera support.
- [x] Added print function.   
- [x] Added support for sound.
- [ ] Add mouse support

### Assets
`assets/drink.wav` under CC0 license
