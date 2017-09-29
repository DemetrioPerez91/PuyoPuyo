#include "defines.h"
#include <vector>
using namespace std;
class Board{
	
public:
	
	Board();
	void render();
	SDL_Surface* loadImg(std::string path);
	void renderNext();
	void setBoard(vector<vector<int>>&);
	void printArr(vector<vector<int>>&);
	void setScreen(SDL_Surface * screen);
	void setNext(int n1,int n2);
	void gameOverScreen();
	void renderScore(int score);
	int score;
	void RealeaseAll();
	void pauseMenu();



private:
	SDL_Surface * red;
	SDL_Surface * green;
	SDL_Surface * yellow;
	SDL_Surface * blue;
	SDL_Surface * bg;
	TTF_Font * scoreText;
	SDL_Surface * scoreSurface;
	SDL_Surface * pauseSurface;

	
	SDL_Surface * GameOver;
	vector<vector<int>> board;
	SDL_Surface * screen;
	int p1,p2;

};
