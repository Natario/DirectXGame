#pragma once

#include "Actor.h"

class Player : public Actor
{
public:
	Player(float x, float y) :
		Actor(x, y)
	{};

	int accel{ 1200 };
	float maxVel{ 300 };
	
	void UpdatePosition(class MainWindow& wnd, bool isGameModeRunaway, float deltaTime) override;
	void Draw(class Graphics& gfx) const override;
	void DrawAlternative(class Graphics& gfx, bool gracePeriod) const;
};

