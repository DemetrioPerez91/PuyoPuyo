#include "defines.h"
#include "Board.h"
#include "Pieces.h"
#include <vector>
class Controller{
public: 
	Controller(SDL_Surface * screen,SDL_Window *window);
	void setScreen (SDL_Surface* screen);
	void setWindow (SDL_Window* window);
	void flow();
	void generatePieces();
	void clearSpace(int x, int y);
	void setPieces(int x, int y,int color);
	void moveDown(Pieces &);
	int randomGem();
	bool nextOccupied(int x,int y);
	void moveRight(Pieces & ,Pieces & );
	void moveLeft(Pieces & ,Pieces & );
	void changePose();
	void changeToPose1();
	void changeToPose2();
	void changeToPose3();
	void changeToPose4();
	bool canChangePose();
	void changeCPUPose();
	void changeCPUToPose1();
	void changeCPUToPose2();
	void changeCPUToPose3();
	void changeCPUToPose4();
	bool canChangeCPUPose();
	void fall(Pieces &);
	void checkForFour();
	void reset();
	void checkNeighbors(int x, int y, int current,vector<int>&,vector<int>&);
	int getPieceFromArray(int x ,int y);
	bool checkCoordinates(int x, int y, vector<int>&,vector<int>&);
	void shiftBoard();
	void shiftCollumn(int x,int &);
	bool checkCollumn(int x,int y);
	Pieces p1;
	Pieces p2;
	Pieces cp1;
	Pieces cp2;
	bool gameover;
	void goScreen();
	void shutDown();
	void pause();
	void changeColors(int x,int y);
	void handlePlayerPieces();
	void handleCPUPieces();
	void generateCPUPieces();
	void moveLeftPlayer();
	void moveRightPLayer();
	bool findCombo(Pieces & , Pieces & );
	int speed;
	int dir;




private:
	SDL_Surface * cScreen;
	SDL_Window * cWindow;
	Mix_Chunk * falling;
	Mix_Chunk * scoring ;		
	Board board;
	vector<vector<int>> pieces;
	int next1;
	int next2;
	Pieces temp;
	int pose;
	bool move;
	bool moveCPU;
	int score;
	int cpose;


};

