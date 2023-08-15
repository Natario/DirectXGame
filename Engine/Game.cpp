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
	if (wnd.kbd.KeyIsPressed(VK_UP))
		yPos -= 5;
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		xPos += 5;
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
		yPos += 5;
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
		xPos -= 5;
	
	if (wnd.kbd.KeyIsPressed(VK_CONTROL))
	{
		colorR = 255;
		colorG = 0;
		colorB = 0;
	}

	isAlternativeShape = wnd.kbd.KeyIsPressed(VK_SHIFT);
}

void Game::ComposeFrame()
{

	if (!isAlternativeShape)
	{
		// Draw crosshair
		// horizontal line
		gfx.PutPixel(xPos - 5, yPos, colorR, colorG, colorB);
		gfx.PutPixel(xPos - 4, yPos, colorR, colorG, colorB);
		gfx.PutPixel(xPos - 3, yPos, colorR, colorG, colorB);
		gfx.PutPixel(xPos + 3, yPos, colorR, colorG, colorB);
		gfx.PutPixel(xPos + 4, yPos, colorR, colorG, colorB);
		gfx.PutPixel(xPos + 5, yPos, colorR, colorG, colorB);
		// vertical line
		gfx.PutPixel(xPos, yPos - 5, colorR, colorG, colorB);
		gfx.PutPixel(xPos, yPos - 4, colorR, colorG, colorB);
		gfx.PutPixel(xPos, yPos - 3, colorR, colorG, colorB);
		gfx.PutPixel(xPos, yPos + 3, colorR, colorG, colorB);
		gfx.PutPixel(xPos, yPos + 4, colorR, colorG, colorB);
		gfx.PutPixel(xPos, yPos + 5, colorR, colorG, colorB);
	}
	else
	{
		// Draw rectangle
		// top line
		gfx.PutPixel(xPos - 5, yPos - 5, colorR, colorG, colorB);
		gfx.PutPixel(xPos - 4, yPos - 5, colorR, colorG, colorB);
		gfx.PutPixel(xPos - 3, yPos - 5, colorR, colorG, colorB);
		gfx.PutPixel(xPos + 3, yPos - 5, colorR, colorG, colorB);
		gfx.PutPixel(xPos + 4, yPos - 5, colorR, colorG, colorB);
		gfx.PutPixel(xPos + 5, yPos - 5, colorR, colorG, colorB);
		// bottom line
		gfx.PutPixel(xPos - 5, yPos + 5, colorR, colorG, colorB);
		gfx.PutPixel(xPos - 4, yPos + 5, colorR, colorG, colorB);
		gfx.PutPixel(xPos - 3, yPos + 5, colorR, colorG, colorB);
		gfx.PutPixel(xPos + 3, yPos + 5, colorR, colorG, colorB);
		gfx.PutPixel(xPos + 4, yPos + 5, colorR, colorG, colorB);
		gfx.PutPixel(xPos + 5, yPos + 5, colorR, colorG, colorB);
		// left line
		gfx.PutPixel(xPos - 5, yPos - 5, colorR, colorG, colorB);
		gfx.PutPixel(xPos - 5, yPos - 4, colorR, colorG, colorB);
		gfx.PutPixel(xPos - 5, yPos - 3, colorR, colorG, colorB);
		gfx.PutPixel(xPos - 5, yPos + 3, colorR, colorG, colorB);
		gfx.PutPixel(xPos - 5, yPos + 4, colorR, colorG, colorB);
		gfx.PutPixel(xPos - 5, yPos + 5, colorR, colorG, colorB);
		// right line
		gfx.PutPixel(xPos + 5, yPos - 5, colorR, colorG, colorB);
		gfx.PutPixel(xPos + 5, yPos - 4, colorR, colorG, colorB);
		gfx.PutPixel(xPos + 5, yPos - 3, colorR, colorG, colorB);
		gfx.PutPixel(xPos + 5, yPos + 3, colorR, colorG, colorB);
		gfx.PutPixel(xPos + 5, yPos + 4, colorR, colorG, colorB);
		gfx.PutPixel(xPos + 5, yPos + 5, colorR, colorG, colorB);
	}
}
