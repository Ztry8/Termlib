#include <stdio.h>
#include "EGA8x8.h"
#include "core.h"

// scale of graphics
#define SCALE 2

const unsigned char BLACK[3] = { 0, 0, 0 };				// 0
const unsigned char GRAY[3] = { 85, 85, 85 };			// 1 
const unsigned char WHITE[3] = { 255, 255, 255 };		// 2

const unsigned char RED[3] = { 255, 0, 0 };				// 3
const unsigned char CORAL[3] = { 255, 85, 85 };			// 4
const unsigned char ORANGE[3] = { 255, 170, 0 };		// 5

const unsigned char GREEN[3] = { 0, 255, 0 };			// 6
const unsigned char DARK_GREEN[3] = { 0, 85, 0 };		// 7
const unsigned char FOREST_GREEN[3] = { 85, 170, 0 };	// 8

const unsigned char BLUE[3] = { 0, 0, 255 };			// 9
const unsigned char CYAN[3] = { 0, 85, 85 };			// 10
const unsigned char AQUA[3] = { 0, 255, 255 };			// 11
const unsigned char EMERALD[3] = { 0, 255, 170 };		// 12

const unsigned char YELLOW[3] = { 255, 255, 0 };		// 13

const unsigned char PINK[3] = { 255, 0, 255 };			// 14
const unsigned char PURPLE[3] = { 170, 0, 170 };		// 15

// init core of engine
unsigned char init_core(struct Core* core) {
	SDL_DisplayMode displayMode;
	if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
		char buffer[128];
		sprintf_s(buffer, 128, "SDL2 couldn't initialize!\nError: %s", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", buffer, NULL);
		return 1;
	}
	SDL_GetDesktopDisplayMode(0,&displayMode);

	SDL_ShowCursor(0);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
	SDL_SetHint(SDL_HINT_APP_NAME, "Province");
	SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");
	SDL_SetHint(SDL_HINT_GRAB_KEYBOARD, "1");
	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
	SDL_SetHint(SDL_HINT_WINDOWS_NO_CLOSE_ON_ALT_F4, "1");

	core->window = SDL_CreateWindow("Province", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIDTH * TILE_W * SCALE, HEIGHT * TILE_H * SCALE, 0);
	//core->window = SDL_CreateWindow("Province", 0, 0, displayMode.w, displayMode.h, 0);	
	if (core->window == NULL) {
		char buffer[128];
		sprintf_s(buffer, 128, "Window couldn't be created!\nError: %s", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", buffer, NULL);
		return 1;
	}

	core->renderer = SDL_CreateRenderer(core->window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
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
		sprintf_s(buffer, 128, "Assets couldn't be loaded!\nTry reinstalling the game or installing the original, not the modified version!\nError: %s", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", buffer, NULL);
		return 1;
	}

	core->gfx = SDL_CreateTextureFromSurface(core->renderer, raw_gfx); SDL_FreeSurface(raw_gfx);
	if (core->gfx == NULL) {
		char buffer[128];
		sprintf_s(buffer, 128, "Assets couldn't initialize!\nTry reinstalling the game or installing the original, not the modified version!\nError: %s", SDL_GetError());
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error!", buffer, NULL);
		return 1;
	}

	if (init_game() != 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Your system doesn't meet the requirements!\nYou need 2GB of free RAM and more to run!", NULL);
		return 1;
	}

	return 0;
}

static const unsigned char* set_color(unsigned char color) {
	if (color == 1) return GRAY;
	else if (color == 2) return WHITE;
	else if (color == 3) return RED;
	else if (color == 4) return CORAL;
	else if (color == 5) return ORANGE;
	else if (color == 6) return GREEN;
	else if (color == 7) return DARK_GREEN;
	else if (color == 8) return FOREST_GREEN;
	else if (color == 9) return BLUE;
	else if (color == 10) return CYAN;
	else if (color == 11) return AQUA;
	else if (color == 12) return EMERALD;
	else if (color == 13) return YELLOW;
	else if (color == 14) return PINK;
	else if (color == 15) return PURPLE;
	else return BLACK;
}

void set_tile(struct Core* core, char symbol, unsigned char color, signed long x, signed long y) {
	SDL_Rect part;
	part.x = TILE_W * (symbol - 32); part.y = 0;
	part.w = TILE_W; part.h = TILE_H;

	SDL_Rect pos;
	pos.x = x * TILE_W; pos.y = y * TILE_H;
	pos.w = TILE_W; pos.h = TILE_H;

	SDL_SetTextureColorMod(core->gfx, set_color(color)[0], set_color(color)[1], set_color(color)[2]);
	SDL_RenderCopy(core->renderer, core->gfx, &part, &pos);
}

// run main loop of game 
void run_core(struct Core* core) {
	SDL_Event e; char quit = 0;
	while (!quit) {
		unsigned long long start = SDL_GetPerformanceCounter();
		while (SDL_PollEvent(&e)) { 
			if (e.type == SDL_QUIT || SDL_GetKeyboardState(NULL)[SDL_SCANCODE_ESCAPE]) quit = 1; 
			if (/*e.key.repeat == 0 &&*/ e.type == SDL_KEYDOWN) input_game(e.key.keysym.scancode);
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