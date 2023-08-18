#include "Player.h"
#include "MainWindow.h"
#include "Graphics.h"
#include "TextDrawer.h"


void Player::UpdatePosition(MainWindow& wnd, bool isGameModeRunaway, float deltaTime)
{
	// increase player speed in the direction of key press
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		if (yVel - accel * deltaTime > -maxVel)
			yVel -= accel * deltaTime;
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		if (xVel + accel * deltaTime < maxVel)
			xVel += accel * deltaTime;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		if (yVel + accel * deltaTime < maxVel)
			yVel += accel * deltaTime;
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		if (xVel - accel * deltaTime > -maxVel)
			xVel -= accel * deltaTime;
	}

	// decrease player speed if no key pressed
	if (!wnd.kbd.KeyIsPressed(VK_UP) && yVel < 0)
		yVel += accel * deltaTime;
	if (!wnd.kbd.KeyIsPressed(VK_DOWN) && yVel > 0)
		yVel -= accel * deltaTime;
	if (!wnd.kbd.KeyIsPressed(VK_RIGHT) && xVel > 0)
		xVel -= accel * deltaTime;
	if (!wnd.kbd.KeyIsPressed(VK_LEFT) && xVel < 0)
		xVel += accel * deltaTime;

	// avoid player moving very slowly due to float roundings (e.g. 0.01432...)
	if (xVel > -5 && xVel < 5)
		xVel = 0.f;
	if (yVel > -5 && yVel < 5)
		yVel = 0.f;

	// update position of player depending on speed only if new position is not outside screen, otherwise stop the movement
	if (canMoveHorizontally(deltaTime))
		x += xVel * deltaTime;
	else
		xVel = 0;
	if (canMoveVertically(deltaTime))
		y += yVel * deltaTime;
	else
		yVel = 0;

	// can also use mouse to move the player in shooting gallery (otherwise player would just move mouse super fast to the next food item while in grace and thus easily avoid enemies
	if (!isGameModeRunaway)
	{
		if (wnd.mouse.IsInWindow() && (wnd.mouse.GetPosX() > 0 + halfsize) && (wnd.mouse.GetPosX() < Graphics::ScreenWidth - halfsize) &&
			(wnd.mouse.GetPosY() > 0 + halfsize) && (wnd.mouse.GetPosY() < Graphics::ScreenHeight - halfsize))
		{
			ShowCursor(false);
			x = (float) wnd.mouse.GetPosX();
			y = (float) wnd.mouse.GetPosY();
		}
	}
}


void Player::Draw(Graphics& gfx) const
{
	// Draw crosshair

	// horizontal line
	for (int i = 0; i <= halfsize / 2 + 5; i++)
	{
		gfx.PutPixel(int(x - halfsize) + i, (int) y, colorR, colorG, colorB);
		gfx.PutPixel(int(x + halfsize) - i, (int) y, colorR, colorG, colorB);
	}
	// vertical line
	for (int i = 0; i <= halfsize / 2 + 5; i++)
	{
		gfx.PutPixel((int) x, int(y - halfsize) + i, colorR, colorG, colorB);
		gfx.PutPixel((int) x, int(y + halfsize) - i, colorR, colorG, colorB);
	}
}

void Player::DrawAlternative(Graphics& gfx, bool gracePeriod) const
{
	TextDrawer::drawImage(gfx, L"img\\quagmire.png", int(x - halfsize), int(y - halfsize));

	// in grace period, draw a rectangle around player so he knows it's in grace
	if (gracePeriod)
	{
		// top line
		for (int i = 0; i <= halfsize / 2; i++)
		{
			gfx.PutPixel(int(x - halfsize) + i, int(y - halfsize), 0, 255, 0);
			gfx.PutPixel(int(x + halfsize) - i, int(y - halfsize), 0, 255, 0);
		}
		// bottom line
		for (int i = 0; i <= halfsize / 2; i++)
		{
			gfx.PutPixel(int(x - halfsize) + i, int(y + halfsize), 0, 255, 0);
			gfx.PutPixel(int(x + halfsize) - i, int(y + halfsize), 0, 255, 0);
		}
		// left line
		for (int i = 0; i <= halfsize / 2; i++)
		{
			gfx.PutPixel(int(x - halfsize), int(y - halfsize) + i, 0, 255, 0);
			gfx.PutPixel(int(x - halfsize), int(y + halfsize) - i, 0, 255, 0);
		}
		// right line
		for (int i = 0; i <= halfsize / 2; i++)
		{
			gfx.PutPixel(int(x + halfsize), int(y - halfsize) + i, 0, 255, 0);
			gfx.PutPixel(int(x + halfsize), int(y + halfsize) - i, 0, 255, 0);
		}
	}
}