#pragma once

#include "Graphics.h"
#include "Actor.h"

class Player : public Actor
{
public:
	Player(int x, int y) :
		Actor(x, y)
	{};

	int accel{ 1 };
	int maxVel{ 5 };
	
	void Draw(Graphics& gfx) override;
};

