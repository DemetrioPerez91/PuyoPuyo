#include "defines.h"
#include "Board.h"
#include <algorithm>
#include <vector>
#include <string>

using namespace std;
//render game over screen

void Board::pauseMenu(){
	SDL_BlitSurface(pauseSurface,NULL,screen,NULL);
}

void Board::RealeaseAll(){
	SDL_FreeSurface(scoreSurface);
	SDL_FreeSurface(red);
	SDL_FreeSurface(green);
	SDL_FreeSurface(yellow);
	SDL_FreeSurface(blue);
	SDL_FreeSurface(bg);
	scoreSurface = NULL;
	red = NULL;
	green = NULL;
	blue = NULL;
	yellow= NULL;
	bg=NULL;


}

void Board::gameOverScreen(){
	SDL_BlitSurface(GameOver,NULL,screen,NULL);
}

//set next pair of gems (unused)
void Board::setNext(int n1, int n2){
	p1 = n1;
	p2 = n2;
}
//set screern for board to render into
void Board::setScreen(SDL_Surface * cScreen){
	screen = cScreen;
}
//print board in console
void Board::printArr(vector<vector<int>>&printing){
	for(int i = 0 ; i<BOARDY;i++){
		for(int j = 0; j<BOARDX;j++){
			printf("%i,",printing.at(i).at(j));
		}
		printf("\n");
	}
	printf("\n");
}

//Render View
//Render next pair of gems
void Board::renderNext(){
	SDL_Rect rect1;
	rect1.x = NEXT_X;
	rect1.y = NEXT_Y1;
	SDL_Rect rect2;
	rect2.x = NEXT_X;
	rect2.y = NEXT_Y2;
	switch(p1){
		case 1:
			SDL_BlitSurface(red,NULL,screen,&rect1);
		break;
		case 2:
			SDL_BlitSurface(green,NULL,screen,&rect1);
		break;
		case 3:
			SDL_BlitSurface(yellow,NULL,screen,&rect1);
		break;
		case 4:
			SDL_BlitSurface(blue,NULL,screen,&rect1);
		break;
	}
	switch(p2){
		case 1:
			SDL_BlitSurface(red,NULL,screen,&rect2);
		break;
		case 2:
			SDL_BlitSurface(green,NULL,screen,&rect2);
		break;
		case 3:
			SDL_BlitSurface(yellow,NULL,screen,&rect2);
		break;
		case 4:
			SDL_BlitSurface(blue,NULL,screen,&rect2);
		break;
	}

}
//Render player's score
void Board::renderScore(int score){
	std::string data =  std::to_string(static_cast<long long>(score));
	SDL_Rect rect;
	rect.x = 820;
	rect.y = 279;
	SDL_Color black = {0,0,0};
	scoreSurface = TTF_RenderText_Solid(scoreText,data.c_str(),black);
	// if( scoreSurface == NULL ) { printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() ); }
	SDL_BlitSurface(scoreSurface,NULL,screen,&rect);
	SDL_FreeSurface(scoreSurface);
}
//render board
void Board::render(){

	
	SDL_BlitSurface(bg,NULL,screen,NULL);
	for(int i = 0; i< BOARDX;i++){
		for(int j = 0; j<BOARDY;j++){
			SDL_Rect rect;
			rect.x = (i*50)+WMIN;
			rect.y = (j*50)+HMIN;
			switch(board.at(j).at(i)){
				case 0:
				break;
				case 1:
					SDL_BlitSurface(red,NULL,screen,&rect);
					//printf("rendering \n");
				break;
				case 2:
					SDL_BlitSurface(green,NULL,screen,&rect);
					//printf("rendering \n");
				break;
				case 3:
					SDL_BlitSurface(yellow,NULL,screen,&rect);
					//printf("rendering \n");
				break;
				case 4:
					SDL_BlitSurface(blue,NULL,screen,&rect);
					//printf("rendering \n");
				break;
				default:

				break;
			}
		}	
	}
	renderNext();
	

	

	
}

//load images for rendering
SDL_Surface * Board::loadImg(std::string path){
	 SDL_Surface *loader = NULL;
    loader = IMG_Load(path.c_str());
    if(loader==NULL){
        printf("SDL SURFACE not initialized SDL_Error: %s \n", SDL_GetError());
        printf("Unable to load surface %s ",path.c_str());
		return NULL;
    }
	return loader;
	
}


//Reasign pieces from controller into board
void Board::setBoard(vector<vector<int>>&newBoard){
	board = newBoard;
	
}
//Constructor
Board::Board(){
	red = loadImg(RED);
	green = loadImg(GREEN);
	yellow = loadImg(YELLOW);
	blue = loadImg(BLUE);
	bg = loadImg(BG);
	GameOver = loadImg(GO);
	pauseSurface = loadImg(PAUSE);
	scoreText =	TTF_OpenFont(BLEACH,30);

	
	//begining board
	board.resize(BOARDY);
	
	for(int i = 0; i<BOARDY;i++){
		board.at(i).resize(BOARDX);
	}
	for(int i  = 0; i< BOARDY;i++){
		for(int J = 0 ; J < BOARDX; J++){
			board.at(i).at(J) = 0;
			
			printf("%i",board.at(i).at(J));

		}
		printf("\n");
	}
}
