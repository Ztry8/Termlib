#pragma once
#include <SDL.h>
#include <stdio.h>
#include "EGA8x8.h"

#define SCALE 2
// size of one tile in px 
#define TILE_W 8 
#define TILE_H 8

// size of window's screen in tiles 
#define WIDTH 80
#define HEIGHT 43

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

const unsigned char BLACK[3] = { 0, 0, 0 };		
const unsigned char BLUE[3] = { 0, 0, 170 };	
const unsigned char GREEN[3] = { 0, 170, 0 };	
const unsigned char CYAN[3] = { 0, 170, 170 };	
const unsigned char RED[3] = { 170, 0, 0 };	
const unsigned char MAGENTA[3] = { 170, 0, 170 };
const unsigned char BROWN[3] = { 170, 85, 0 };
const unsigned char LIGHT_GRAY[3] = { 170, 170, 170 };	
const unsigned char DARK_GRAY[3] = { 85, 85, 85 };	
const unsigned char BRIGHT_BLUE[3] = { 85, 85, 255 };	
const unsigned char BRIGHT_GREEN[3] = { 85, 255, 85 };	
const unsigned char BRIGHT_CYAN[3] = { 85, 255, 255 };	
const unsigned char BRIGHT_RED[3] = { 255, 85, 85 };
const unsigned char BRIGHT_MAGENTA[3] = { 255, 85, 255 };
const unsigned char BRIGHT_YELLOW[3] = { 255, 255, 85 };
const unsigned char BRIGHT_WHITE[3] = { 255, 255, 255 };

struct Core {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* gfx;
};

unsigned char init_game();
void input_game(SDL_Scancode);
void update_core(struct Core*);
void shutdown_game();

unsigned char init_core(struct Core* core) {
	SDL_DisplayMode displayMode;
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
		char buffer[128];
		sprintf_s(buffer, 128, "SDL2 couldn't initialize!\nError: %s", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", buffer, NULL);
		return 1;
	}

	SDL_ShowCursor(0);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
	SDL_SetHint(SDL_HINT_APP_NAME, "Engine");
	SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");
	SDL_SetHint(SDL_HINT_GRAB_KEYBOARD, "1");
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
	SDL_SetHint(SDL_HINT_WINDOWS_NO_CLOSE_ON_ALT_F4, "1");

	core->window = SDL_CreateWindow("Province", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIDTH * TILE_W * SCALE, HEIGHT * TILE_H * SCALE, 0);
	if (core->window == NULL) {
		char buffer[128];
		sprintf_s(buffer, 128, "Window couldn't be created!\nError: %s", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", buffer, NULL);
		return 1;
	}

	core->renderer = SDL_CreateRenderer(core->window, -1, SDL_RENDERER_ACCELERATED);
	if (core->renderer == NULL) {
		char buffer[128];
		sprintf_s(buffer, 128, "Renderer couldn't be created!\nError: %s", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", buffer, NULL);
		return 1;
	}
	SDL_RenderSetLogicalSize(core->renderer, WIDTH * TILE_W * SCALE, HEIGHT * TILE_H * SCALE);
	SDL_RenderSetScale(core->renderer, SCALE, SCALE);
	
	SDL_Surface* raw_gfx = SDL_CreateRGBSurfaceFrom((void*)font.pixel_data, font.width, font.height,
		font.bytes_per_pixel * 8, font.bytes_per_pixel * font.width, 0x000000ff, 0x0000ff00, 0x00ff0000,
		(font.bytes_per_pixel == 3) ? 0 : 0xff000000);

	if (raw_gfx == NULL) {
		char buffer[128];
		sprintf_s(buffer, 128, "Assets couldn't be loaded!\nError: %s", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", buffer, NULL);
		return 1;
	}

	core->gfx = SDL_CreateTextureFromSurface(core->renderer, raw_gfx); SDL_FreeSurface(raw_gfx);
	if (core->gfx == NULL) {
		char buffer[128];
		sprintf_s(buffer, 128, "Assets couldn't initialize!\nError: %s", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", buffer, NULL);
		return 1;
	}

	if (init_game() != 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Your system doesn't meet the requirements!", NULL);
		return 1;
	}

	return 0;
}

static const unsigned char* set_color(unsigned char color) {
	if (color == 0) return BLACK;
	else if (color == 1) return BLUE;
	else if (color == 2) return GREEN;
	else if (color == 3) return CYAN;
	else if (color == 4) return RED;
	else if (color == 5) return MAGENTA;
	else if (color == 6) return BROWN;
	else if (color == 7) return LIGHT_GRAY;
	else if (color == 8) return DARK_GRAY;
	else if (color == 9) return BRIGHT_BLUE;
	else if (color == 10) return BRIGHT_GREEN;
	else if (color == 11) return BRIGHT_CYAN;
	else if (color == 12) return BRIGHT_RED;
	else if (color == 13) return BRIGHT_MAGENTA;
	else if (color == 14) return BRIGHT_YELLOW;
	else return BRIGHT_WHITE;
}

void set_tile(struct Core* core, char symbol, unsigned char color, long x, long y) {
	SDL_Rect part;
	part.x = TILE_W * (symbol - 32); part.y = 0;
	part.w = TILE_W; part.h = TILE_H;

	SDL_Rect pos;
	pos.x = x * TILE_W; pos.y = y * TILE_H;
	pos.w = TILE_W; pos.h = TILE_H;

	SDL_SetTextureColorMod(core->gfx, set_color(color)[0], set_color(color)[1], set_color(color)[2]);
	SDL_RenderCopy(core->renderer, core->gfx, &part, &pos);
}

void run_core(struct Core* core) {
	SDL_Event e; char quit = 0;
	while (!quit) {
		unsigned long long start = SDL_GetPerformanceCounter();
		while (SDL_PollEvent(&e)) { 
			if (e.type == SDL_QUIT || SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE]) quit = 1; 
			if (e.type == SDL_KEYDOWN) input_game(e.key.keysym.scancode);
		}

		SDL_RenderClear(core->renderer);
		update_core(core);
		SDL_RenderPresent(core->renderer);

		unsigned long long end = SDL_GetPerformanceCounter();
		float elapsed = 1.f / ((end - start) / (float)SDL_GetPerformanceFrequency());
		char buffer[128]; sprintf_s(buffer, 128, "Current FPS: %0.0f", elapsed);
		SDL_SetWindowTitle(core->window, buffer);
	}
}

void shutdown_core(struct Core* core) {
	shutdown_game();
	SDL_DestroyTexture(core->gfx);
	SDL_DestroyRenderer(core->renderer);
	SDL_DestroyWindow(core->window);
	SDL_Quit();
}
