#pragma once
#include <SDL.h>

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHT_GRAY 7
#define DARK_GRAY 8
#define BRIGHT_BLUE 9
#define BRIGHT_GREEN 10
#define BRIGHT_CYAN 11
#define BRIGHT_RED 12
#define BRIGHT_MAGENTA 13
#define BRIGHT_YELLOW 14
#define BRIGHT_WHITE 15

// size of one tile in px 
#define TILE_W 8 
#define TILE_H 8

// size of window's screen in tiles 
#define WIDTH 80
#define HEIGHT 43

struct Core {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* gfx;
};

unsigned char init_core(struct Core*);
unsigned char init_game();
void shutdown_game();
void input_game(SDL_Scancode);
void set_tile(struct Core*, char, unsigned char, signed long, signed long);
void run_core(struct Core*);
void shutdown_core(struct Core*);
void update_core(struct Core*);
