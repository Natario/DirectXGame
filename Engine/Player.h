#pragma once

#include "Actor.h"

class Player : public Actor
{
public:
	Player(int x, int y) :
		Actor(x, y)
	{};

	int accel{ 1 };
	int maxVel{ 5 };
	
	void UpdatePosition(class MainWindow& wnd) override;
	void Draw(class Graphics& gfx) const override;
	void DrawAlternative(class Graphics& gfx, bool gracePeriod) const;
};

