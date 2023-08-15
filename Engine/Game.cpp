/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	// increase speed in direction of key press
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		if(abs(yVel) < maxVel)
			yVel -= accel;
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		if (abs(xVel) < maxVel)
			xVel += accel;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		if (abs(yVel) < maxVel)
			yVel += accel;
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		if (abs(xVel) < maxVel)
			xVel -= accel;
	}
	
	// decellerate if no key pressed
	if (!wnd.kbd.KeyIsPressed(VK_UP) && yVel < 0)
		yVel += accel;
	if (!wnd.kbd.KeyIsPressed(VK_DOWN) && yVel > 0)
		yVel -= accel;
	if (!wnd.kbd.KeyIsPressed(VK_RIGHT) && xVel > 0)
		xVel -= accel;
	if (!wnd.kbd.KeyIsPressed(VK_LEFT) && xVel < 0)
		xVel += accel;
	
	// update position depending on speed if new position is not outside screen (plus a margin for all the recticle pixels)
	if ((xPos + xVel > 0 + crosshairSize) && (xPos + xVel < Graphics::ScreenWidth - crosshairSize))
		xPos += xVel;
	else
		xVel = 0;
	if ((yPos + yVel > 0 + crosshairSize) && (yPos + yVel < Graphics::ScreenHeight - crosshairSize))
		yPos += yVel;
	else
		yVel = 0;
	
	// detect colision with enemy
	if((xPos <= xEnemy + crosshairSize) && (xPos >= xEnemy - crosshairSize) && (yPos <= yEnemy + crosshairSize) && (yPos >= yEnemy - crosshairSize))
	{
		colorR = 255;
		colorG = 0;
		colorB = 0;
	}
	else
	{
		colorR = 255;
		colorG = 255;
		colorB = 255;
	}

	// change shape of recticle
	isAlternativeShape = wnd.kbd.KeyIsPressed(VK_SHIFT);
}

void Game::ComposeFrame()
{

	if (!isAlternativeShape)
	{
		drawCrosshair(xPos, yPos, colorR, colorG, colorB);
	}
	else
	{
		drawRectangle(xPos, yPos, colorR, colorG, colorB);
	}

	// enemy rectangle
	drawRectangle(xEnemy, yEnemy, 255, 255, 255);
}

void Game::drawCrosshair(int xPos, int yPos, int colorR, int colorG, int colorB)
{
	// horizontal line
	gfx.PutPixel(xPos - crosshairSize + 0, yPos, colorR, colorG, colorB);
	gfx.PutPixel(xPos - crosshairSize + 1, yPos, colorR, colorG, colorB);
	gfx.PutPixel(xPos - crosshairSize + 2, yPos, colorR, colorG, colorB);
	gfx.PutPixel(xPos + crosshairSize - 2, yPos, colorR, colorG, colorB);
	gfx.PutPixel(xPos + crosshairSize - 1, yPos, colorR, colorG, colorB);
	gfx.PutPixel(xPos + crosshairSize - 0, yPos, colorR, colorG, colorB);
	// vertical line
	gfx.PutPixel(xPos, yPos - crosshairSize + 0, colorR, colorG, colorB);
	gfx.PutPixel(xPos, yPos - crosshairSize + 1, colorR, colorG, colorB);
	gfx.PutPixel(xPos, yPos - crosshairSize + 2, colorR, colorG, colorB);
	gfx.PutPixel(xPos, yPos + crosshairSize - 2, colorR, colorG, colorB);
	gfx.PutPixel(xPos, yPos + crosshairSize - 1, colorR, colorG, colorB);
	gfx.PutPixel(xPos, yPos + crosshairSize - 0, colorR, colorG, colorB);
}

void Game::drawRectangle(int xPos, int yPos, int colorR, int colorG, int colorB)
{
	// top line
	gfx.PutPixel(xPos - crosshairSize + 0, yPos - crosshairSize, colorR, colorG, colorB);
	gfx.PutPixel(xPos - crosshairSize + 1, yPos - crosshairSize, colorR, colorG, colorB);
	gfx.PutPixel(xPos - crosshairSize + 2, yPos - crosshairSize, colorR, colorG, colorB);
	gfx.PutPixel(xPos + crosshairSize - 2, yPos - crosshairSize, colorR, colorG, colorB);
	gfx.PutPixel(xPos + crosshairSize - 1, yPos - crosshairSize, colorR, colorG, colorB);
	gfx.PutPixel(xPos + crosshairSize - 0, yPos - crosshairSize, colorR, colorG, colorB);
	// bottom line
	gfx.PutPixel(xPos - crosshairSize + 0, yPos + crosshairSize, colorR, colorG, colorB);
	gfx.PutPixel(xPos - crosshairSize + 1, yPos + crosshairSize, colorR, colorG, colorB);
	gfx.PutPixel(xPos - crosshairSize + 2, yPos + crosshairSize, colorR, colorG, colorB);
	gfx.PutPixel(xPos + crosshairSize - 2, yPos + crosshairSize, colorR, colorG, colorB);
	gfx.PutPixel(xPos + crosshairSize - 1, yPos + crosshairSize, colorR, colorG, colorB);
	gfx.PutPixel(xPos + crosshairSize - 0, yPos + crosshairSize, colorR, colorG, colorB);
	// left line
	gfx.PutPixel(xPos - crosshairSize, yPos - crosshairSize + 0, colorR, colorG, colorB);
	gfx.PutPixel(xPos - crosshairSize, yPos - crosshairSize + 1, colorR, colorG, colorB);
	gfx.PutPixel(xPos - crosshairSize, yPos - crosshairSize + 2, colorR, colorG, colorB);
	gfx.PutPixel(xPos - crosshairSize, yPos + crosshairSize - 2, colorR, colorG, colorB);
	gfx.PutPixel(xPos - crosshairSize, yPos + crosshairSize - 1, colorR, colorG, colorB);
	gfx.PutPixel(xPos - crosshairSize, yPos + crosshairSize - 0, colorR, colorG, colorB);
	// right line		crosshairSize
	gfx.PutPixel(xPos + crosshairSize, yPos - crosshairSize + 0, colorR, colorG, colorB);
	gfx.PutPixel(xPos + crosshairSize, yPos - crosshairSize + 1, colorR, colorG, colorB);
	gfx.PutPixel(xPos + crosshairSize, yPos - crosshairSize + 2, colorR, colorG, colorB);
	gfx.PutPixel(xPos + crosshairSize, yPos + crosshairSize - 2, colorR, colorG, colorB);
	gfx.PutPixel(xPos + crosshairSize, yPos + crosshairSize - 1, colorR, colorG, colorB);
	gfx.PutPixel(xPos + crosshairSize, yPos + crosshairSize - 0, colorR, colorG, colorB);
}
