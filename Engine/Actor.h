#pragma once

class Actor
{
public:
	Actor(float x, float y, float xVel = 0, float yVel = 0) :
		x{ x },
		y{ y },
		xVel{ xVel },
		yVel{ yVel }
	{}; 

	float x;
	float y;
	float xVel;
	float yVel;
	float halfsize{ 20 };
	int colorR{ 255 };
	int colorG{ 255 };
	int colorB{ 255 };

	bool canMoveHorizontally(float deltaTime);
	bool canMoveVertically(float deltaTime);
	virtual void UpdatePosition(class MainWindow& wnd, bool isGameModeRunaway, float deltaTime) = 0;
	virtual void Draw(class Graphics& gfx) const = 0;
};

