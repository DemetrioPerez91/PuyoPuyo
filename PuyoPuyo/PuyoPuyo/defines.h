#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED

//import SDL Librraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_test.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <string>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

//Windows dimensions
#define SCREEN_H 800
#define SCREEN_W 1200

//Gem's spawning points
#define NEXT_X 863
#define NEXT_Y1 70
#define NEXT_Y2 120
#define HMIN 70
#define HMAX 620
#define WMIN 130
#define WMAX 380

//Board's dimensions

#define BOARDX 12
//#define BOARDX 6
#define BOARDY 12

//URLS of thefiles used in the game
#define BLEACH "img\\bleach.ttf"
#define JTHEME "img\\jtheme.mp3"
//#define BG "img\\bg.png"
#define BG "img\\bgDouble.png"
#define GREEN "img\\green.png"
#define BLUE "img\\blue.png"
#define RED "img\\red.png"
#define YELLOW "img\\yellow.png"
#define GO "img\\GameOver.png"
#define PAUSE "img\\pause.png"








#endif // DEFINES_H_INCLUDED
