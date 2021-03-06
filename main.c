#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <direct.h>
#include <time.h>
#include <stdlib.h>
#include <SDL_ttf.h>

SDL_Event event;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Renderer* sunny;
SDL_Surface* surface_base = NULL;
SDL_Texture* texture_base = NULL;
SDL_Surface* surface_block = NULL;
SDL_Texture* texture_block = NULL;
SDL_Surface* surface_menugame = NULL;
SDL_Texture* texture_menugame = NULL;
SDL_Surface* surface_background = NULL;
SDL_Texture* texture_background = NULL;
SDL_Surface* surface_bomb = NULL;
SDL_Texture* texture_bomb = NULL;

int delay_function(delay_diff) {  //delay
	int delay = delay_diff / 60 - SDL_GetTicks() + SDL_GetTicks();
	SDL_Delay(delay);
	return 0;
}

int main(int argc, char* args[]) {
	int status = 1;
	int base_x = 320, blockx = 380, blocky = 0, gameover_x = 800, count = 1, speed = 2, scorex = 680, posmenu = 0, highscore = 0,
		highscorex = 800, highscorey = 0, level = 1, levelx = 800, scorey = 50, scorewidth = 100, scorehieght = 50, restartx = 800,
		bombx = 700, bomby = 0, dropbomb = 1;
	int score = 0;
	char a[100];
	char scoretext[10], highscoretext[20], leveltext[10], restart[50], img[20];

	srand(time(NULL));
	TTF_Init();
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Drop Block", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	surface_background = IMG_Load("image/background.png");
	texture_background = SDL_CreateTextureFromSurface(renderer, surface_background);
	surface_base = IMG_Load("image/base.png"); // load image
	texture_base = SDL_CreateTextureFromSurface(renderer, surface_base);
	surface_menugame = IMG_Load("image/menu.png");
	texture_menugame = SDL_CreateTextureFromSurface(renderer, surface_menugame);
	surface_block = IMG_Load("image/1.png");
	texture_block = SDL_CreateTextureFromSurface(renderer, surface_block);
	surface_bomb = IMG_Load("image/bomb.png");
	texture_bomb = SDL_CreateTextureFromSurface(renderer, surface_bomb);

	sprintf(scoretext, "Score : %d", score);
	sprintf(highscoretext, "High score : %d", highscore);
	sprintf(leveltext, "Level : %d", level);

	TTF_Font* sans = TTF_OpenFont("font/COOPBL.TTF", 100);   //Load font 
	SDL_Color black = { 0, 0, 0 };   //Set black color
	SDL_Color white = { 255, 255, 255 };
	SDL_Color red = { 255, 0, 0 };
	SDL_Color blue = { 0, 155, 255 };
	SDL_Surface* surface_score = TTF_RenderText_Solid(sans, scoretext, white);   //Create Variable for turn text
	SDL_Texture* texture_score = SDL_CreateTextureFromSurface(renderer, surface_score);
	SDL_Surface* surface_gameover = TTF_RenderText_Solid(sans, "Game Over", red);
	SDL_Texture* texture_gameover = SDL_CreateTextureFromSurface(renderer, surface_gameover);
	SDL_Surface* surface_highscore = TTF_RenderText_Solid(sans, highscoretext, white);
	SDL_Texture* texture_highscore = SDL_CreateTextureFromSurface(renderer, surface_highscore);
	SDL_Surface* surface_level = TTF_RenderText_Solid(sans, leveltext, white);
	SDL_Texture* texture_level = SDL_CreateTextureFromSurface(renderer, surface_level);
	SDL_Surface* surface_restart = TTF_RenderText_Solid(sans, "Press key down to restart", blue);
	SDL_Texture* texture_restart = SDL_CreateTextureFromSurface(renderer, surface_restart);

	while (status) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				status = 0;
			}
		}
        	if (SDL_PollEvent) {
			if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_LEFT: // move bar to left side
					if (count == 0) {
						base_x -= 10;
					}
					break;
				case SDLK_RIGHT: // move bar to right side 
					if (count == 0) {
						base_x += 10;
					}
					break;
				case SDLK_DOWN: // restart game
					if (count == 1) {
						scorex = 680;
						scorey = 50;
						scorewidth = 100;
						scorehieght = 50;
						gameover_x = 800;
						base_x = 320;
						blocky = 0;
						count = 0;
						blockx = (rand() % (720 - 0 + 1) + 0);
						score = 0;
						highscorex = 580;
						highscorey = 0;
						levelx = 680;
						level = 1;
						restartx = 800;
						dropbomb = (rand() % (3 - 0 + 1) + 0);
						bombx = (rand() % (720 - 0 + 1) + 0);
						bomby = 0;
						sprintf(scoretext, "Score : %d", score);
						surface_score = TTF_RenderText_Solid(sans, scoretext, white);
						texture_score = SDL_CreateTextureFromSurface(renderer, surface_score);
						sprintf(highscoretext, "High score : %d", highscore);
						surface_highscore = TTF_RenderText_Solid(sans, highscoretext, white);
						texture_highscore = SDL_CreateTextureFromSurface(renderer, surface_highscore);
						sprintf(leveltext, "Level : %d", level);
						surface_level = TTF_RenderText_Solid(sans, leveltext, white);
						texture_level = SDL_CreateTextureFromSurface(renderer, surface_level);
						speed = 2;
					}
					break;
				case SDLK_UP: // start game
					count = 0;
					posmenu = 800;
					highscorex = 580;
					levelx = 680;
					break;
				default:
					break;
				}
			}
		}
		if (base_x < 0 && count == 0) {
			base_x = 0;
		}

		if (base_x > 680 && count == 0) {
			base_x = 680;
		}

		if ((blocky >= 500 && blocky <= 540) && ((base_x - 40 <= blockx && base_x + 120 >= blockx) || (base_x == blockx))) {
			blocky = 0;
			blockx = (rand() % (720 - 0 + 1) + 0);
			score += 1;
			if (score % 10 == 0 && score != 0) {
				speed += 1;
				level += 1;
				sprintf(leveltext, "Level : %d", level);
				surface_level = TTF_RenderText_Solid(sans, leveltext, white);
				texture_level = SDL_CreateTextureFromSurface(renderer, surface_level);
			}
			sprintf(scoretext, "Score : %d", score);
			surface_score = TTF_RenderText_Solid(sans, scoretext, white);
			texture_score = SDL_CreateTextureFromSurface(renderer, surface_score);
			if (score > highscore) {
				highscore += 1;
				sprintf(highscoretext, "High score : %d", highscore);
				surface_highscore = TTF_RenderText_Solid(sans, highscoretext, white);
				texture_highscore = SDL_CreateTextureFromSurface(renderer, surface_highscore);
			}
		} // count score and update score

		else if (blocky >= 600) {
			count = 1;
			gameover_x = 150;
			scorex = 325;
			scorey = 260;
			scorewidth = 150;
			scorehieght = 50;
			base_x = 800;
			highscorex = 270;
			highscorey = 310;
			levelx = 800;
			restartx = 200;
			bombx = 800;
		} // game over

		else if ((bomby >= 500 && bomby <= 540) && ((base_x - 40 <= bombx && base_x + 120 >= bombx) || (base_x == bombx))) {
			count = 1;
			gameover_x = 150;
			scorex = 325;
			scorey = 260;
			scorewidth = 150;
			scorehieght = 50;
			base_x = 800;
			highscorex = 270;
			highscorey = 310;
			levelx = 800;
			restartx = 200;
			bombx = 800;
			blockx = 800;
		} // game over

		if (bomby >= 600) {
			dropbomb = (rand() % (3 - 0 + 0) + 0);
			if (dropbomb != 2) {
				bombx = 800;
				bomby = 0;
			}
			else {
				bombx = (rand() % (720 - 0 + 0) + 0);
				bomby = 0;
			}
		}

		if (count == 0) {
			blocky += speed;
			bomby += speed;
		} // speed drops
    		SDL_Rect menu0 = { 0, 0, 800, 600 }; // pos background
		SDL_Rect menu1 = { base_x, 530, 130, 10 }; // pos bar
		SDL_Rect menu2 = { blockx, blocky, 40, 40 };  // pos block
		SDL_Rect menu3 = { scorex, scorey, scorewidth, scorehieght }; // pos score
		SDL_Rect menu4 = { gameover_x, 100, 500, 100 }; // pos game over 
		SDL_Rect menu5 = { posmenu, 0, 800, 600 }; // pos menugame
		SDL_Rect menu6 = { highscorex, highscorey, 200, 50 }; //pos high score
		SDL_Rect menu7 = { levelx, 100, 100, 50 }; // pos level
		SDL_Rect menu8 = { restartx, 470, 400, 50 }; // pos restart
		SDL_Rect bomb = { bombx, bomby, 50, 50 }; // pos bomb

		SDL_RenderCopy(renderer, texture_background, NULL, &menu0);
		SDL_RenderCopy(renderer, texture_base, NULL, &menu1);
		SDL_RenderCopy(renderer, texture_block, NULL, &menu2);
		SDL_RenderCopy(renderer, texture_bomb, NULL, &bomb);
		SDL_RenderCopy(renderer, texture_score, NULL, &menu3);
		SDL_RenderCopy(renderer, texture_gameover, NULL, &menu4);
		SDL_RenderCopy(renderer, texture_menugame, NULL, &menu5);
		SDL_RenderCopy(renderer, texture_highscore, NULL, &menu6);
		SDL_RenderCopy(renderer, texture_level, NULL, &menu7);
		SDL_RenderCopy(renderer, texture_restart, NULL, &menu8);

		SDL_RenderPresent(renderer);
		delay_function(500);
		SDL_RenderClear(renderer);
	}
	return 0;
}
