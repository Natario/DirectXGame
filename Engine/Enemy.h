#pragma once

#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy(float x, float y, float xVel, float yVel) :
		Actor(x, y, xVel, yVel)
	{};

	bool isAlive{ true };
	
	void UpdatePosition(MainWindow& wnd, bool isGameModeRunaway, float deltaTime) override;
	void Draw(class Graphics& gfx) const override;
	void DrawAlternative(class Graphics& gfx) const;
};

