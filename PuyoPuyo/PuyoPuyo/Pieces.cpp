#include "Pieces.h"

//get/set funcitons

Pieces::Pieces(){cpu = false;}
int Pieces::getX(){return x;}
int Pieces::getY(){return y;}
int Pieces::getColor(){return color;}
void Pieces::setFallAlone(bool fall){fallAlone=fall;}
bool Pieces::getFallAllone(){return fallAlone;}
void Pieces::setX(int xi){x = xi;}
void Pieces::setY(int yi){y=yi;}
void Pieces::setColor(int colori){color= colori;}
void Pieces::setCPU(){cpu=true;}
bool Pieces::isCPU(){return cpu;}

