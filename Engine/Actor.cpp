#include "Actor.h"
#include "Graphics.h"

bool Actor::canMoveHorizontally(float deltaTime)
{
	if ((x + xVel*deltaTime > 0 + halfsize) && (x + xVel*deltaTime < Graphics::ScreenWidth - halfsize))
		return true;
	else
		return false;
}

bool Actor::canMoveVertically(float deltaTime)
{
	if ((y + yVel*deltaTime > 0 + halfsize) && (y + yVel*deltaTime < Graphics::ScreenHeight - halfsize))
		return true;
	else
		return false;
}
