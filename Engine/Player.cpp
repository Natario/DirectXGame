#include "Player.h"
#include "MainWindow.h"
#include "Graphics.h"
#include "TextDrawer.h"


void Player::UpdatePosition(MainWindow& wnd, bool isGameModeRunaway)
{
	// increase player speed in the direction of key press
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		if (yVel - accel > -maxVel)
			yVel -= accel;
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		if (xVel + accel < maxVel)
			xVel += accel;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		if (yVel + accel < maxVel)
			yVel += accel;
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		if (xVel - accel > -maxVel)
			xVel -= accel;
	}

	// decrease player speed if no key pressed
	if (!wnd.kbd.KeyIsPressed(VK_UP) && yVel < 0)
		yVel += accel;
	if (!wnd.kbd.KeyIsPressed(VK_DOWN) && yVel > 0)
		yVel -= accel;
	if (!wnd.kbd.KeyIsPressed(VK_RIGHT) && xVel > 0)
		xVel -= accel;
	if (!wnd.kbd.KeyIsPressed(VK_LEFT) && xVel < 0)
		xVel += accel;

	// update position of player depending on speed only if new position is not outside screen, otherwise stop the movement
	if (canMoveHorizontally())
		x += xVel;
	else
		xVel = 0;
	if (canMoveVertically())
		y += yVel;
	else
		yVel = 0;

	// can also use mouse to move the player in shooting gallery (otherwise player would just move mouse super fast to the next food item while in grace and thus easily avoid enemies
	if (!isGameModeRunaway)
	{
		if (wnd.mouse.IsInWindow() && (wnd.mouse.GetPosX() > 0 + halfsize) && (wnd.mouse.GetPosX() < Graphics::ScreenWidth - halfsize) &&
			(wnd.mouse.GetPosY() > 0 + halfsize) && (wnd.mouse.GetPosY() < Graphics::ScreenHeight - halfsize))
		{
			ShowCursor(false);
			x = wnd.mouse.GetPosX();
			y = wnd.mouse.GetPosY();
		}
	}
}


void Player::Draw(Graphics& gfx) const
{
	// Draw crosshair

	// horizontal line
	for (int i = 0; i <= halfsize / 2 + 5; i++)
	{
		gfx.PutPixel(x - halfsize + i, y, colorR, colorG, colorB);
		gfx.PutPixel(x + halfsize - i, y, colorR, colorG, colorB);
	}
	// vertical line
	for (int i = 0; i <= halfsize / 2 + 5; i++)
	{
		gfx.PutPixel(x, y - halfsize + i, colorR, colorG, colorB);
		gfx.PutPixel(x, y + halfsize - i, colorR, colorG, colorB);
	}
}

void Player::DrawAlternative(Graphics& gfx, bool gracePeriod) const
{
	TextDrawer::drawImage(gfx, L"img\\quagmire.png", x - halfsize, y - halfsize);

	// in grace period, draw a rectangle around player so he knows it's in grace
	if (gracePeriod)
	{
		// top line
		for (int i = 0; i <= halfsize / 2; i++)
		{
			gfx.PutPixel(x - halfsize + i, y - halfsize, 0, 255, 0);
			gfx.PutPixel(x + halfsize - i, y - halfsize, 0, 255, 0);
		}
		// bottom line
		for (int i = 0; i <= halfsize / 2; i++)
		{
			gfx.PutPixel(x - halfsize + i, y + halfsize, 0, 255, 0);
			gfx.PutPixel(x + halfsize - i, y + halfsize, 0, 255, 0);
		}
		// left line
		for (int i = 0; i <= halfsize / 2; i++)
		{
			gfx.PutPixel(x - halfsize, y - halfsize + i, 0, 255, 0);
			gfx.PutPixel(x - halfsize, y + halfsize - i, 0, 255, 0);
		}
		// right line
		for (int i = 0; i <= halfsize / 2; i++)
		{
			gfx.PutPixel(x + halfsize, y - halfsize + i, 0, 255, 0);
			gfx.PutPixel(x + halfsize, y + halfsize - i, 0, 255, 0);
		}
	}
}