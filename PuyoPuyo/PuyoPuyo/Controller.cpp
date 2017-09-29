#include "Controller.h"
bool Controller::findCombo(Pieces & p1, Pieces & p2){
	vector <int> xCor;
	vector<int> yCor;
	int p1X =p1.getX();
	int p2X = p2.getX();
	int p1Y = p1.getY();
	int p2Y = p2.getY();
	for (int i = p1Y+1; i < BOARDY; i++){
		if(pieces.at(i).at(p1X) !=0){
			if(pieces.at(i).at(p1X) == p1.getColor()){
				printf("same color %i, %i", i,p1X);
				checkNeighbors(p1X,i,p1.getColor(),xCor,yCor);
				//printf("printing neighbors list\n");
				for(int k = 0; k< xCor.size();k++){
					//printf("%i,%i\n",xCor.at(k),yCor.at(k));
				}
				if(xCor.size()>=3){	
					xCor.clear();
					yCor.clear();
					return true;
				}
				
				
			}else{
				i =999;
			}

		}
		
		
		
	}
	for (int i = p2Y+1; i < BOARDY; i++){
		if(pieces.at(i).at(p2X) !=0){
			if(pieces.at(i).at(p2X) == p2.getColor()){
				printf("same color %i, %i", i,p2X);
				return true;
				
			}else{
				i =999;
			}

		}
		
		
		
	}
	return false;
}

void Controller::handleCPUPieces(){
	int curx = 0;
	if(cp1.getY()+1<BOARDY&&cp2.getY()+1<BOARDY){
		
		switch(pose){
			case 1:
				if(nextOccupied(cp1.getX(),cp1.getY()+1)||nextOccupied(cp2.getX(),cp2.getY()+1)){
					if(nextOccupied(cp1.getX(),cp1.getY()+1)){
						move = false;
						fall(cp2);
					}else if(nextOccupied(cp2.getX(),cp2.getY()+1)){
						move = false;
						fall(cp1);
					}
					else{
						move= true;
					
						generateCPUPieces();

					}
				}
				else{
					fall(cp1);
					fall(cp2);
				}
			break;
			case 2:
				if(nextOccupied(cp2.getX(),cp2.getY()+1)){
				
					generateCPUPieces();			
				}
				else{
					fall(cp2);
					fall(cp1);			
				}
			break;
			case 4:
				if(nextOccupied(cp1.getX(),cp1.getY()+1)){
				
					generateCPUPieces();			
				}
				else{
					fall(cp1);
					fall(cp2);
				}
			break;
			case 3:
				if(nextOccupied(cp1.getX(),cp1.getY()+1)||nextOccupied(cp2.getX(),cp2.getY()+1)){
					if(nextOccupied(cp1.getX(),cp1.getY()+1)){
						move = false;
						fall(cp2);
					}else if(nextOccupied(cp2.getX(),cp2.getY()+1)){
						move = false;
						fall(cp1);
					}
					else{
						move= true;
						
						generateCPUPieces();	
					}				
				}
				else{
					fall(cp1);
					fall(cp2);
				}
						
			break;
		}
		if(!findCombo(cp1,cp2)){
			if(dir == 0){
				curx = cp1.getX();
				moveRight(cp1,cp2);
				if(curx==cp1.getX()){
					dir =1;
				}
			}
			else{
				
				curx = cp1.getX();
				moveLeft(cp1,cp2);
				if(curx==cp1.getX()){
					dir =0;
				}
			}
		}
	}else{
		
		generateCPUPieces();	

	}
}
//normal flow of pieces controll
void Controller::flow(){
	
	handlePlayerPieces();
	handleCPUPieces();
	setPieces(cp1.getX(),cp1.getY(),cp1.getColor());
	setPieces(cp2.getX(),cp2.getY(),cp2.getColor());
	setPieces(p1.getX(),p1.getY(),p1.getColor());
	setPieces(p2.getX(),p2.getY(),p2.getColor());
	board.setBoard(pieces);
	//render board
	board.render();
	
	//board.printArr(pieces);	
	board.renderScore(score);
}
//change gems colors
void Controller::changeColors(int x, int y){
	int currentColor = pieces.at(y).at(x);
	vector <int> xCor;
	vector<int> yCor;
	bool changing = true;
	while(changing){
		if(currentColor != 0){
			currentColor++;
			if(currentColor>4){
				currentColor=1;
			}
			setPieces(x,y,currentColor);
			checkNeighbors(x,y,currentColor,xCor,yCor);
					//printf("printing neighbors list\n");
					for(int k = 0; k< xCor.size();k++){
						//printf("%i,%i\n",xCor.at(k),yCor.at(k));
					}
					if(xCor.size()<=3){		
						setPieces(x,y,currentColor);
						printf("color changed");
						changing = false;
					}
					xCor.clear();
					yCor.clear();
		}
		else{
			changing = false;
		}
	}
	
}

//pauseGame
void Controller::pause(){
	board.pauseMenu();
}
//Shut game Down
void Controller::shutDown(){
	board.RealeaseAll();
}
//reset game
void Controller::reset(){
	for(int i = 0; i< BOARDY; i++){
		for(int j = 0; j < BOARDX; j++){
			pieces.at(i).at(j)=0;
		}
	}
	p1.setX(2);
	p1.setY(0);
	p2.setX(3);
	p2.setY(0);
	cp1.setX(8);
	cp1.setY(0);
	cp2.setX(9);
	cp2.setY(0);
	score = 0;

	board.setBoard(pieces);
	gameover = false;
	board.render();
	board.renderScore(score);

}
//set game over screen
void Controller::goScreen(){
	board.gameOverScreen();
}
//movePieces after removing groups of four or more
void Controller::shiftCollumn(int x,int & y){
	
	for(int i = y; i>0;i--){
		printf("%i,%i\n",i,x);
		int newy = i-1;
		temp.setX(x);temp.setY(i);
		temp.setColor(pieces.at(newy).at(x));
		//int y = temp.getY();

		clearSpace(temp.getX(),temp.getY());
		
		
		//printf("cleared\n");
		
		setPieces(temp.getX(),temp.getY(),temp.getColor());
		printf("collum shifting\n");
		board.printArr(pieces);
		board.setBoard(pieces);
		board.render();
		SDL_UpdateWindowSurface(cWindow);

	}
	if(!nextOccupied(x,y)){
		
		shiftCollumn(x,y);
	}
}
bool Controller::checkCollumn(int x, int y){
	for(int i = y; i>=0;i--){
		if(pieces.at(i).at(x)!=0){
			return true;
		}
	
	}
		return false;
}
void Controller::shiftBoard(){
	setPieces(cp1.getX(),cp1.getY(),0);
	setPieces(cp2.getX(),cp2.getY(),0);
	setPieces(p1.getX(),p1.getY(),0);
	setPieces(p2.getX(),p2.getY(),0);
	printf("shifting Board\n");
	for(int i = 11 ; i >=0; i--){
		for(int j = 0; j < BOARDX; j++){
			
			if(i-1>=0){
				if(!nextOccupied(j,i)){
					if(checkCollumn(j,i)){
						shiftCollumn(j,i);
						
					}
				}
			}
			
		}
	}

	
}

//find four or more pieces connected
bool Controller::checkCoordinates(int x, int y, vector<int>&xCor,vector<int>&yCor){
	if(xCor.size()!=0){
		for(int i = 0; i<xCor.size();i++ ){
			if(x == xCor.at(i)&&y==yCor.at(i)){
				
				return false;
			}
		}
	}
	xCor.push_back(x);
	yCor.push_back(y);
	return true;
}
void Controller::checkNeighbors(int x, int y, int current, vector<int>&xCor,vector<int>&yCor){
	//checkFor upper neighbors
	
	if(checkCoordinates(x,y,xCor,yCor)){
		if(y-1 >= 0){
			if(nextOccupied(x,y-1)){
				if(current ==getPieceFromArray(x,y-1)){
					checkNeighbors(x,y-1,current,xCor,yCor);
				}
			}	
		}
		if(x-1 >= 0){
			if(nextOccupied(x-1,y)){
				if(current ==getPieceFromArray(x-1,y)){
					checkNeighbors(x-1,y,current,xCor,yCor);
				}
			}
	
		}
		if(y+1 < BOARDY){
			if(nextOccupied(x,y+1)){
				if(current ==getPieceFromArray(x,y+1)){
					checkNeighbors(x,y+1,current,xCor,yCor);
				}
			}
	
		}
		if(x+1 < BOARDX){
			if(nextOccupied(x+1,y)){
				if(current ==getPieceFromArray(x+1,y)){
					checkNeighbors(x+1,y,current,xCor,yCor);
				}
			}
	
		}
	}
	
}
void Controller::checkForFour(){
	vector <int> xCor;
	vector<int> yCor;
	int current;
	int currentX;
	int currentY;
	for(int i = 0 ; i < BOARDY; i++){
		for(int j = 0 ; j < BOARDX; j++){
			current = pieces.at(i).at(j);
			currentX = j;
			currentY = i;
			if(current==0){
			}
			else{
				checkNeighbors(currentX,currentY,current,xCor,yCor);
				//printf("printing neighbors list\n");
				for(int k = 0; k< xCor.size();k++){
					//printf("%i,%i\n",xCor.at(k),yCor.at(k));
				}
				if(xCor.size()>=4){	
					for(int l = 0; l< xCor.size();l++){
						clearSpace(xCor.at(l),yCor.at(l));
						Mix_PlayChannel(-1,scoring,0);
					}
					score += xCor.size()*50;
					speed = 10;
					SDL_Delay(speed);
					shiftBoard();
					
				}
				xCor.clear();
				yCor.clear();
			}
		}
	}	
	speed = 150;

}

//get the color of a piece in any part of the array
int Controller::getPieceFromArray(int x, int y){
	return pieces.at(y).at(x);
}

//controll of pose(rotation)
bool Controller::canChangePose(){
	
	switch (pose){
		case 1:
			if(p1.getX()-1>=0&&!nextOccupied(p2.getX()-1,p2.getY())){
				
				return true;
			}else if(!nextOccupied(BOARDX-1,p2.getY())){
				return true;
			}
			pose = 4;
			
		break;
		case 2:
			if(p1.getY()-1>=0&&!nextOccupied(p2.getX(),p2.getY()-1)){
				return true;
			}
			

			pose = 1;
		break;
		case 3:
			if(p1.getX()+1<BOARDX&&!nextOccupied(p2.getX()+1,p2.getY())){
				return true;
			}else if(!nextOccupied(0,p2.getY())){
				return true;
			}
			pose = 2;
		break;
		case 4:
			if(p1.getY()+1<BOARDY&&!nextOccupied(p2.getX(),p2.getY()+1)){
				return true;
			}
			pose = 3;
		break;
	
	}

	
	
	return false;
}
void Controller::changeToPose1(){
	
	p1.setY(p1.getY()-1);
	if(p1.getX()-1<0){
		p1.setX(BOARDX-1);
		clearSpace(0,p1.getY()+1);
	}else{
		p1.setX(p1.getX()-1);
		clearSpace(p1.getX()+1,p1.getY()+1);
	}
	
	setPieces(p1.getX(),p1.getY(),p1.getColor());
	setPieces(p2.getX(),p2.getY(),p2.getColor());
	
}
void Controller::changeToPose2(){
	p1.setY(p1.getY()-1);
	if(p1.getX()+1>= BOARDX){
		p1.setX(0);
		clearSpace(BOARDX-1,p1.getY()+1);
	}else{
		p1.setX(p1.getX()+1);
		clearSpace(p1.getX()-1,p1.getY()+1);
	}
	
	setPieces(p1.getX(),p1.getY(),p1.getColor());
	setPieces(p2.getX(),p2.getY(),p2.getColor());
	
}
void Controller::changeToPose3(){

	p1.setY(p1.getY()+1);
	if(p1.getX()+1>=BOARDX){
		p1.setX(0);
		clearSpace(BOARDX-1,p1.getY()-1);
	}else{
		p1.setX(p1.getX()+1);
		clearSpace(p1.getX()-1,p1.getY()-1);
	}
	
	setPieces(p1.getX(),p1.getY(),p1.getColor());
	setPieces(p2.getX(),p2.getY(),p2.getColor());
	
}
void Controller::changeToPose4(){
	p1.setY(p1.getY()+1);
	if(p1.getX()-1<0){
		p1.setX(BOARDX-1);
		clearSpace(0,p1.getY()-1);
	}else{
		p1.setX(p1.getX()-1);
		clearSpace(p1.getX()+1,p1.getY()-1);
	}
	setPieces(p1.getX(),p1.getY(),p1.getColor());
	setPieces(p2.getX(),p2.getY(),p2.getColor());
	
}
void Controller::changePose(){
	if(move){
		if(pose==4){
			pose=1;
		}else{
			pose++;
		}
		switch(pose){
		case 1:
			
			 
			if(canChangePose()){changeToPose1();}
			break;
		case 2:

			if(canChangePose()){changeToPose2();}
			break;
		case 3:

			if(canChangePose()){changeToPose3();}
			break;
		case 4:
			if(canChangePose()){changeToPose4();}
			break;
		}
		//board.printArr(pieces);
	}
	printf("pose: %i\n",pose);
	board.setBoard(pieces);
		board.render();
		SDL_UpdateWindowSurface(cWindow);

}

//sideways movement controll
void Controller::moveLeftPlayer(){
	moveLeft(p1,p2);
}
void Controller::moveRightPLayer(){
	moveRight(p1,p2);
}
void Controller::moveLeft(Pieces & p1,Pieces & p2){
	if(move){
		switch(pose){
		//horizontal 1
		case 1:
			if(p1.getX()-1>=0){
				if(!nextOccupied(p1.getX()-1,p1.getY())){
					if(p2.getX()==0){
						
						clearSpace(p2.getX(),p2.getY());
						p2.setX(BOARDX-1);
						p1.setX(p1.getX()-1);
						clearSpace(p1.getX()+1,p1.getY());
					}else{
						p2.setX(p2.getX()-1);
						clearSpace(p2.getX()+1,p2.getY());
		
						p1.setX(p1.getX()-1);
						clearSpace(p1.getX()+1,p1.getY());
				
					}
					
				}

			}
			else if(p1.getX()==0){
				if(!nextOccupied(BOARDX-1,p1.getY())){
				//case 1
					p2.setX(p2.getX()-1);
					clearSpace(p2.getX()+1,p2.getY());
					clearSpace(p1.getX()+1,p1.getY());
					p1.setX(BOARDX-1);
				
				
				}
				printf("lol");
			}
			

		break;
		//vert 1
		case 2:
			if(p1.getX()-1>=0){
				if(!nextOccupied(p1.getX()-1,p1.getY())&&!nextOccupied(p2.getX()-1,p2.getY())){
			
					p2.setX(p2.getX()-1);
					clearSpace(p2.getX()+1,p2.getY());
		
					p1.setX(p1.getX()-1);
					clearSpace(p1.getX()+1,p1.getY());
				
				}

			}
			else if (p1.getX()==0){
				
				if(!nextOccupied(BOARDX-1,p1.getY())&&!nextOccupied(BOARDX-1,p2.getY())){
			
					p2.setX(BOARDX-1);
					clearSpace(0,p2.getY());
		
					p1.setX(BOARDX-1);
					clearSpace(0,p1.getY());
				
				}


			}
		break;
		//horizontal 2
		case 3:
			if(p2.getX()-1>=0){
				if(!nextOccupied(p2.getX()-1,p2.getY())){
					if(p1.getX()==0){
						
						clearSpace(p1.getX(),p1.getY());
						p1.setX(BOARDX-1);
						p2.setX(p2.getX()-1);
						clearSpace(p2.getX()+1,p2.getY());
					}else{
						p1.setX(p1.getX()-1);
						clearSpace(p1.getX()+1,p1.getY());
		
						p2.setX(p2.getX()-1);
						clearSpace(p2.getX()+1,p2.getY());
				
					}
					
				}

			}
			else if(p2.getX()==0){
				if(!nextOccupied(BOARDX-1,p2.getY())){
				//case 1
					p1.setX(p1.getX()-1);
					clearSpace(p1.getX()+1,p1.getY());
					clearSpace(p2.getX()+1,p2.getY());
					p2.setX(BOARDX-1);
				
				
				}
				printf("lol");
			}
			/*if(p2.getX()-1>=0){
				if(!nextOccupied(p2.getX()-1,p2.getY())){
			
				p2.setX(p2.getX()-1);
				clearSpace(p2.getX()+1,p2.getY());
		
				p1.setX(p1.getX()-1);
				clearSpace(p1.getX()+1,p1.getY());
				
				}

			}*/
		break;
		//vert 2
		case 4:
			if(p1.getX()-1>=0){
				if(!nextOccupied(p1.getX()-1,p1.getY())&&!nextOccupied(p2.getX()-1,p2.getY())){
				
					board.printArr(pieces);
					p1.setX(p1.getX()-1);
					clearSpace(p1.getX()+1,p1.getY());
		
					p2.setX(p2.getX()-1);
					clearSpace(p2.getX()+1,p2.getY());
				}
			
			}
			else if (p1.getX()==0){
				
				if(!nextOccupied(BOARDX-1,p1.getY())&&!nextOccupied(BOARDX-1,p2.getY())){
			
					p2.setX(BOARDX-1);
					clearSpace(0,p2.getY());
		
					p1.setX(BOARDX-1);
					clearSpace(0,p1.getY());
				
				}


			}
		break;

		}
		setPieces(p1.getX(),p1.getY(),p1.getColor());
		setPieces(p2.getX(),p2.getY(),p2.getColor());
		board.setBoard(pieces);
		board.render();
		SDL_UpdateWindowSurface(cWindow);

	
		}
}
void Controller::moveRight(Pieces & p1,Pieces & p2){
	
	if(move){
		switch(pose){
			//hor 1
			case 1:
				if(p2.getX()+1<BOARDX){
					if(p1.getX()==BOARDX-1){
						if(!nextOccupied(p2.getX()+1,p2.getY())){
			
							p2.setX(p2.getX()+1);
							clearSpace(p2.getX()-1,p2.getY());
							p1.setX(0);
							clearSpace(BOARDX-1,p1.getY());
					

						}
					}else{
						if(!nextOccupied(p2.getX()+1,p2.getY())){
			
							p2.setX(p2.getX()+1);
							clearSpace(p2.getX()-1,p2.getY());
							p1.setX(p1.getX()+1);
							clearSpace(p1.getX()-1,p1.getY());
					

						}
					}
				
				}else if(p2.getX()==BOARDX-1){
					if(!nextOccupied(0,p2.getY())){
			
						p2.setX(0);
						clearSpace(BOARDX-1,p2.getY());
						p1.setX(p1.getX()+1);
						clearSpace(p1.getX()-1,p1.getY());
					

					}
				}




			break;
			//ver 1
			case 2: 
				if(p2.getX()+1<BOARDX){
					if(!nextOccupied(p2.getX()+1,p2.getY())&&!nextOccupied(p1.getX()+1,p1.getY())){
			
					p1.setX(p1.getX()+1);
		
					clearSpace(p1.getX()-1,p1.getY());
					p2.setX(p2.getX()+1);
					clearSpace(p2.getX()-1,p2.getY());
				

					}
				}else if(p2.getX()==BOARDX-1){
					if(!nextOccupied(0,p2.getY())&&!nextOccupied(0,p1.getY())){
			
					clearSpace(p1.getX(),p1.getY());
					p1.setX(0);
					clearSpace(p2.getX(),p2.getY());
					p2.setX(0);
		
				

					}
				}
				break;
			//hor 2
			case 3:
				/*if(p1.getX()+1<BOARDX){
					if(!nextOccupied(p1.getX()+1,p1.getY())){
			
					p2.setX(p2.getX()+1);
		
					clearSpace(p2.getX()-1,p2.getY());
					p1.setX(p1.getX()+1);
					clearSpace(p1.getX()-1,p1.getY());
					

					}
				}*/
				if(p1.getX()+1<BOARDX){
					if(p2.getX()==BOARDX-1){
						if(!nextOccupied(p1.getX()+1,p1.getY())){
			
							p1.setX(p1.getX()+1);
							clearSpace(p1.getX()-1,p1.getY());
							p2.setX(0);
							clearSpace(BOARDX-1,p2.getY());
					

						}
					}else{
						if(!nextOccupied(p1.getX()+1,p1.getY())){
			
							p1.setX(p1.getX()+1);
							clearSpace(p1.getX()-1,p1.getY());
							p2.setX(p2.getX()+1);
							clearSpace(p2.getX()-1,p2.getY());
					

						}
					}
				
				}else if(p1.getX()==BOARDX-1){
					if(!nextOccupied(0,p1.getY())){
			
						p1.setX(0);
						clearSpace(BOARDX-1,p1.getY());
						p2.setX(p2.getX()+1);
						clearSpace(p2.getX()-1,p2.getY());
					

					}
				}


			break;
			//ver 2
			case 4:
				if(p2.getX()+1<BOARDX){
					if(!nextOccupied(p2.getX()+1,p2.getY())&&!nextOccupied(p1.getX()+1,p1.getY())){
					p1.setX(p1.getX()+1);
					clearSpace(p1.getX()-1,p1.getY());
					p2.setX(p2.getX()+1);
					clearSpace(p2.getX()-1,p2.getY());
					}
				}
				else if(p2.getX()== BOARDX-1){
					if(!nextOccupied(0,p2.getY())&&!nextOccupied(0,p1.getY())){
						clearSpace(p1.getX(),p1.getY());
						p1.setX(0);
						clearSpace(p2.getX(),p2.getY());
						p2.setX(0);
					}
				}
			break;
		}
		board.setBoard(pieces);
		board.render();
		SDL_UpdateWindowSurface(cWindow);

		setPieces(p1.getX(),p1.getY(),p1.getColor());
		setPieces(p2.getX(),p2.getY(),p2.getColor());
	}
	
}
bool Controller::nextOccupied(int x,int y){
	if(pieces.at(y).at(x)==0){
		return false;
	}
	return true;
}
//move pieces down 1 slot
void Controller::moveDown(Pieces & piece){
	if(piece.getY()+1<BOARDY){
		int y = piece.getY();
		y++;
		clearSpace(piece.getX(),piece.getY());
		piece.setY(y++);
		//printf("cleared\n");
		
		setPieces(p1.getX(),p1.getY(),p1.getColor());
		setPieces(p2.getX(),p2.getY(),p2.getColor());

		//board.printArr(pieces);
	}
}
//set piece color in pieces array
void Controller::setPieces(int x, int y,int color){
	pieces.at(y).at(x)= color;
}

//downward movement controll
void Controller::fall(Pieces & p){
			if(nextOccupied(p.getX(),p.getY()+1)){
				if(!p.isCPU()){
					generatePieces();
				}
				else{
					generateCPUPieces();
				}
			}else{
				
				moveDown(p);
			}
}

//generate a randomly colored gem
int Controller::randomGem(){
	double x = rand()/static_cast<double>(RAND_MAX);
	int that = 1 + static_cast<int>( x * (5 -1 ) );
	return that;
}
//set the screen ion the controller
void Controller::setScreen(SDL_Surface * screen){
	cScreen=screen ;
}
//set the window in the controller
void Controller::setWindow(SDL_Window *window){
	cWindow = window;
}
//set any space in the pieces array to 0
void Controller::clearSpace(int x, int y){
	pieces.at(y).at(x)= 0;
}
//handle Player Pieces
void Controller::handlePlayerPieces(){
	if(p1.getY()+1<BOARDY&&p2.getY()+1<BOARDY){

		switch(pose){
			case 1:
				if(nextOccupied(p1.getX(),p1.getY()+1)||nextOccupied(p2.getX(),p2.getY()+1)){
					if(nextOccupied(p1.getX(),p1.getY()+1)){
						move = false;
						fall(p2);
					}else if(nextOccupied(p2.getX(),p2.getY()+1)){
						move = false;
						fall(p1);
					}
					else{
						move= true;
					
						generatePieces();

					}
				}
				else{
					fall(p1);
					fall(p2);
				}
			break;
			case 2:
				if(nextOccupied(p2.getX(),p2.getY()+1)){
				
					generatePieces();			
				}
				else{
					fall(p2);
					fall(p1);			
				}
			break;
			case 4:
				if(nextOccupied(p1.getX(),p1.getY()+1)){
				
					generatePieces();			
				}
				else{
					fall(p1);
					fall(p2);
				}
			break;
			case 3:
				if(nextOccupied(p1.getX(),p1.getY()+1)||nextOccupied(p2.getX(),p2.getY()+1)){
					if(nextOccupied(p1.getX(),p1.getY()+1)){
						move = false;
						fall(p2);
					}else if(nextOccupied(p2.getX(),p2.getY()+1)){
						move = false;
						fall(p1);
					}
					else{
						move= true;
						
						generatePieces();	
					}				
				}
				else{
					fall(p1);
					fall(p2);
				}
						
			break;
		}
	}else{
		
		generatePieces();	

	}
}

//generate cpu pieces

void Controller::generateCPUPieces(){
	if(pieces.at(0).at(8)==0&&pieces.at(0).at(9)==0){
		
		checkForFour();
		cp1.setX(8);
		cp1.setY(0);
		cp1.setColor(next1);
		cp2.setX(9);
		cp2.setY(0);
		cp2.setColor(next2);
		next1 = randomGem();
		next2 = randomGem();
		board.setNext(next1,next2);
		move= true;

		Mix_PlayChannel(-1,falling,0);
		gameover = false;
	}
	else{
		gameover = true;
	}
}



//generate player pieces
void Controller::generatePieces(){
	if(pieces.at(0).at(2)==0&&pieces.at(0).at(3)==0){
		
		checkForFour();
		p1.setX(2);
		p1.setY(0);
		p1.setColor(next1);
		p2.setX(3);
		p2.setY(0);
		p2.setColor(next2);
		
		next1 = randomGem();
		next2 = randomGem();
		board.setNext(next1,next2);
		pose = 1;
		move= true;
		
		Mix_PlayChannel(-1,falling,0);
		gameover = false;
	}
	else{
		gameover = true;
	}
}
//Constructor
Controller::Controller(SDL_Surface *screen,SDL_Window* window):board(){
	score = 0;
	falling = Mix_LoadWAV("img\\fall.wav");
		scoring = Mix_LoadWAV("img\\score.wav");
	
	next1 = randomGem();
	next2 = randomGem();
	setWindow(window);
	setScreen(screen);
	pieces.resize(BOARDY);

	cp1.setCPU();
	cp2.setCPU();
	
	for(int i = 0; i<BOARDY;i++){
		pieces.at(i).resize(BOARDX);
	}
	for(int i  = 0; i< BOARDY;i++){
		for(int J = 0 ; J < BOARDX; J++){
			pieces.at(i).at(J) = 0;
		}
		
	}
	move = true;
	board.setScreen(cScreen);	
	pose = 1;
	generatePieces();
	generateCPUPieces();
	speed = 150;
	//0 = right 1 = left
	dir = 0;
}
