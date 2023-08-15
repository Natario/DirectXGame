#pragma once

#include "Graphics.h"

class Actor
{
public:
	Actor(int x, int y, int xVel = 0, int yVel = 0) :
		x{ x },
		y{ y },
		xVel{ xVel },
		yVel{ yVel }
	{}; 

	int x;
	int y;
	int xVel;
	int yVel;
	int halfsize{ 20 };
	int colorR{ 255 };
	int colorG{ 255 };
	int colorB{ 255 };

	bool canMoveHorizontally();
	bool canMoveVertically();
	virtual void Draw(Graphics& gfx) const;
};

