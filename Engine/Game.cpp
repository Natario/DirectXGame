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
#include <random>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	std::random_device seed;
	std::mt19937 gen{ seed() };
	std::uniform_int_distribution<> distX{ crosshairHalfSize, Graphics::ScreenWidth - crosshairHalfSize - 1};
	std::uniform_int_distribution<> distY{ crosshairHalfSize, Graphics::ScreenHeight - crosshairHalfSize - 1};
	for(int i = 0 ; i < enemyAmount ; i++)
		enemies.push_back(Enemy{ distX(gen),distY(gen) });
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
		if(yVel - accel > -maxVel)
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
	
	// decellerate if no key pressed
	if (!wnd.kbd.KeyIsPressed(VK_UP) && yVel < 0)
		yVel += accel;
	if (!wnd.kbd.KeyIsPressed(VK_DOWN) && yVel > 0)
		yVel -= accel;
	if (!wnd.kbd.KeyIsPressed(VK_RIGHT) && xVel > 0)
		xVel -= accel;
	if (!wnd.kbd.KeyIsPressed(VK_LEFT) && xVel < 0)
		xVel += accel;
	
	// update position depending on speed only if new position is not outside screen, otherwise stop the crosshair
	if (canMoveHorizontally(xPos, xVel))
		xPos += xVel;
	else
		xVel = 0;
	if (canMoveVertically(yPos, yVel))
		yPos += yVel;
	else
		yVel = 0;
	
	// detect colision with enemy
	bool isColliding = false;
	for (auto& enemy : enemies) {
		if (isOverlapping(xPos, yPos, enemy.x, enemy.y) && enemy.alive)
		{
			isColliding = true;
			if(wnd.kbd.KeyIsPressed(VK_SPACE))
				enemy.alive = false;
		}
	}
	if(isColliding)
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
		DrawCrosshair(xPos, yPos, colorR, colorG, colorB);
	}
	else
	{
		DrawRectangle(xPos, yPos, colorR, colorG, colorB);
	}

	// enemy rectangle
	for (auto& enemy : enemies) {
		if(enemy.alive)
			DrawRectangle(enemy.x, enemy.y, 255, 255, 255);
	}
}

void Game::DrawCrosshair(int xPos, int yPos, int colorR, int colorG, int colorB)
{
	// horizontal line
	for (int i = 0; i <= crosshairHalfSize / 2; i++)
	{
		gfx.PutPixel(xPos - crosshairHalfSize + i, yPos, colorR, colorG, colorB);
		gfx.PutPixel(xPos + crosshairHalfSize - i, yPos, colorR, colorG, colorB);
	}
	// vertical line
	for (int i = 0; i <= crosshairHalfSize / 2; i++)
	{
		gfx.PutPixel(xPos, yPos - crosshairHalfSize + i, colorR, colorG, colorB);
		gfx.PutPixel(xPos, yPos + crosshairHalfSize - i, colorR, colorG, colorB);
	}
}

void Game::DrawRectangle(int xPos, int yPos, int colorR, int colorG, int colorB)
{
	// top line
	for (int i = 0; i <= crosshairHalfSize / 2; i++)
	{
		gfx.PutPixel(xPos - crosshairHalfSize + i, yPos - crosshairHalfSize, colorR, colorG, colorB);
		gfx.PutPixel(xPos + crosshairHalfSize - i, yPos - crosshairHalfSize, colorR, colorG, colorB);
	}
	// bottom line
	for (int i = 0; i <= crosshairHalfSize / 2; i++)
	{
		gfx.PutPixel(xPos - crosshairHalfSize + i, yPos + crosshairHalfSize, colorR, colorG, colorB);
		gfx.PutPixel(xPos + crosshairHalfSize - i, yPos + crosshairHalfSize, colorR, colorG, colorB);
	}
	// left line
	for (int i = 0; i <= crosshairHalfSize / 2; i++)
	{
		gfx.PutPixel(xPos - crosshairHalfSize, yPos - crosshairHalfSize + i, colorR, colorG, colorB);
		gfx.PutPixel(xPos - crosshairHalfSize, yPos + crosshairHalfSize - i, colorR, colorG, colorB);
	}
	// right line
	for (int i = 0; i <= crosshairHalfSize / 2; i++)
	{
		gfx.PutPixel(xPos + crosshairHalfSize, yPos - crosshairHalfSize + i, colorR, colorG, colorB);
		gfx.PutPixel(xPos + crosshairHalfSize, yPos + crosshairHalfSize - i, colorR, colorG, colorB);
	}
}

bool Game::isOverlapping(int xPos, int yPos, int xEnemy, int yEnemy)
{
	return (xPos <= xEnemy + crosshairHalfSize) && (xPos >= xEnemy - crosshairHalfSize) && (yPos <= yEnemy + crosshairHalfSize) && (yPos >= yEnemy - crosshairHalfSize);
}

bool Game::canMoveHorizontally(int xPos, int xVel)
{
	if ((xPos + xVel > 0 + crosshairHalfSize) && (xPos + xVel < Graphics::ScreenWidth - crosshairHalfSize))
		return true;
	else
		return false;
}

bool Game::canMoveVertically(int yPos, int yVel)
{
	if ((yPos + yVel > 0 + crosshairHalfSize) && (yPos + yVel < Graphics::ScreenHeight - crosshairHalfSize))
		return true;
	else
		return false;
}
