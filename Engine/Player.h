#pragma once

#include "Graphics.h"
#include "Actor.h"

class Player : public Actor
{
public:
	Player(int x, int y) :
		Actor(x, y),
		accel{ 1 },
		maxVel{ 5 }
	{};
	int accel;
	int maxVel;
	void Draw(Graphics& gfx) override;
};

