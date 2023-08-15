#pragma once

#include "Graphics.h"

class Actor
{
public:
	Actor(int x, int y, int xVel = 0, int yVel = 0) :
		x{ x },
		y{ y },
		xVel{ xVel },
		yVel{ yVel },
		halfsize{ 10 },
		colorR{ 255 },
		colorG{ 255 },
		colorB{ 255 }
	{}; 
	int x;
	int y;
	int xVel;
	int yVel;
	int halfsize;
	int colorR;
	int colorG;
	int colorB; 
	bool canMoveHorizontally();
	bool canMoveVertically();
	virtual void Draw(Graphics& gfx);
};

