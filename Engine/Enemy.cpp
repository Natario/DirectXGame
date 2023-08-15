#include "Enemy.h"

void Enemy::Draw(Graphics& gfx)
{
	// draw rectangular crosshair
	// top line
	for (int i = 0; i <= halfsize / 2; i++)
	{
		gfx.PutPixel(x - halfsize + i, y - halfsize, colorR, colorG, colorB);
		gfx.PutPixel(x + halfsize - i, y - halfsize, colorR, colorG, colorB);
	}
	// bottom line
	for (int i = 0; i <= halfsize / 2; i++)
	{
		gfx.PutPixel(x - halfsize + i, y + halfsize, colorR, colorG, colorB);
		gfx.PutPixel(x + halfsize - i, y + halfsize, colorR, colorG, colorB);
	}
	// left line
	for (int i = 0; i <= halfsize / 2; i++)
	{
		gfx.PutPixel(x - halfsize, y - halfsize + i, colorR, colorG, colorB);
		gfx.PutPixel(x - halfsize, y + halfsize - i, colorR, colorG, colorB);
	}
	// right line
	for (int i = 0; i <= halfsize / 2; i++)
	{
		gfx.PutPixel(x + halfsize, y - halfsize + i, colorR, colorG, colorB);
		gfx.PutPixel(x + halfsize, y + halfsize - i, colorR, colorG, colorB);
	}
}
