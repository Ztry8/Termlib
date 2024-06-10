#pragma once
#include <SDL.h>

#define INDEX_BLACK 0
#define INDEX_GRAY 1 
#define INDEX_WHITE 2
#define INDEX_RED 3
#define INDEX_CORAL 4
#define INDEX_ORANGE 5
#define INDEX_GREEN 6
#define INDEX_DARK_GREEN 7
#define INDEX_FOREST_GREEN 8
#define INDEX_BLUE 9
#define INDEX_CYAN 10
#define INDEX_AQUA 11
#define INDEX_EMERALD 12
#define INDEX_YELLOW 13
#define INDEX_PINK 14
#define INDEX_PURPLE 15

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