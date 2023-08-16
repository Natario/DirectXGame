#pragma once

#include "Graphics.h"
#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy(int x, int y, int xVel, int yVel) :
		Actor(x, y, xVel, yVel)
	{};

	bool isAlive{ true };
	
	void UpdatePosition(MainWindow& wnd) override;
	void Draw(Graphics& gfx) const override;
};

