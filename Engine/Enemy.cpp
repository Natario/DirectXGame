#include "Enemy.h"

#include "Graphics.h"
#include "TextDrawer.h"

void Enemy::UpdatePosition(MainWindow& wnd)
{
	// make enemy bounce when it hits the screen edge
	if (canMoveHorizontally())
		x += xVel;
	else
		xVel = -xVel;
	if (canMoveVertically())
		y += yVel;
	else
		yVel = -yVel;
}


void Enemy::Draw(Graphics& gfx) const
{

	// Draw rectangular crosshair
	 
	//// top line
	//for (int i = 0; i <= halfsize / 2; i++)
	//{
	//	gfx.PutPixel(x - halfsize + i, y - halfsize, colorR, colorG, colorB);
	//	gfx.PutPixel(x + halfsize - i, y - halfsize, colorR, colorG, colorB);
	//}
	//// bottom line
	//for (int i = 0; i <= halfsize / 2; i++)
	//{
	//	gfx.PutPixel(x - halfsize + i, y + halfsize, colorR, colorG, colorB);
	//	gfx.PutPixel(x + halfsize - i, y + halfsize, colorR, colorG, colorB);
	//}
	//// left line
	//for (int i = 0; i <= halfsize / 2; i++)
	//{
	//	gfx.PutPixel(x - halfsize, y - halfsize + i, colorR, colorG, colorB);
	//	gfx.PutPixel(x - halfsize, y + halfsize - i, colorR, colorG, colorB);
	//}
	//// right line
	//for (int i = 0; i <= halfsize / 2; i++)
	//{
	//	gfx.PutPixel(x + halfsize, y - halfsize + i, colorR, colorG, colorB);
	//	gfx.PutPixel(x + halfsize, y + halfsize - i, colorR, colorG, colorB);
	//}


	// Draw full rectangle

	//for (int i = 0; i <= halfsize * 2; i++)
	//{
	//	for (int j = 0; j <= halfsize * 2; j++)
	//	{
	//		gfx.PutPixel(x - halfsize + j, y - halfsize + i, colorR, colorG, colorB);
	//	}
	//}


	// Draw custom target image (https://www.pngwing.com/en/free-png-zhzsw)
	
	TextDrawer::drawImage(gfx, L"..\\img\\target.png", x - halfsize, y - halfsize);

}

