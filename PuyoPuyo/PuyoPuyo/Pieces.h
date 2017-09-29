#include "defines.h"
#include <string>
class Pieces{
public:

	Pieces();
	int getX();
	int getY();
	int getColor();
	void setX(int xi);
	void setY(int yi);
	void setColor(int colori);
	void moveDown();
	bool getFallAllone();
	void setFallAlone(bool fall);
	void setCPU ();
	bool isCPU();
	
private:
	int x;
	int y;
	int color;
	bool fallAlone;
	bool cpu;

};