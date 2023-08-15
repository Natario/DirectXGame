#include "Player.h"

void Player::Draw(Graphics& gfx)
{
	// draw crosshair
	// horizontal line
	for (int i = 0; i <= halfsize / 2; i++)
	{
		gfx.PutPixel(x - halfsize + i, y, colorR, colorG, colorB);
		gfx.PutPixel(x + halfsize - i, y, colorR, colorG, colorB);
	}
	// vertical line
	for (int i = 0; i <= halfsize / 2; i++)
	{
		gfx.PutPixel(x, y - halfsize + i, colorR, colorG, colorB);
		gfx.PutPixel(x, y + halfsize - i, colorR, colorG, colorB);
	}
}
