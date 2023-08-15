#include "Actor.h"

bool Actor::canMoveHorizontally()
{
	if ((x + xVel > 0 + halfsize) && (x + xVel < Graphics::ScreenWidth - halfsize))
		return true;
	else
		return false;
}

bool Actor::canMoveVertically()
{
	if ((y + yVel > 0 + halfsize) && (y + yVel < Graphics::ScreenHeight - halfsize))
		return true;
	else
		return false;
}

void Actor::Draw(Graphics& gfx) const
{
}
