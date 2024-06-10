#pragma once
#include <SDL.h>

#define INDEX_BLACK 0
#define INDEX_BLUE 1
#define INDEX_GREEN 2
#define INDEX_CYAN 3
#define INDEX_RED 4
#define INDEX_MAGENTA 5
#define INDEX_BROWN 6
#define INDEX_LIGHT_GRAY 7
#define INDEX_DARK_GRAY 8
#define INDEX_BRIGHT_BLUE 9
#define INDEX_BRIGHT_GREEN 10
#define INDEX_BRIGHT_CYAN 11
#define INDEX_BRIGHT_RED 12
#define INDEX_BRIGHT_MAGENTA 13
#define INDEX_BRIGHT_YELLOW 14
#define INDEX_BRIGHT_WHITE 15

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
