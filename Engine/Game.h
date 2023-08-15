/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Enemy.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void DrawCrosshair(int xPos, int yPos, int colorR, int colorG, int colorB);
	void DrawRectangle(int xPos, int yPos, int colorR, int colorG, int colorB);
	bool isOverlapping(int xPos, int yPos, int xEnemy, int yEnemy);
	bool canMoveHorizontally(int xPos, int xVel);
	bool canMoveVertically(int yPos, int yVel);
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	int xPos{ Graphics::ScreenWidth / 2 };
	int yPos{ Graphics::ScreenHeight / 2 };
	int xVel{ 0 };
	int yVel{ 0 };
	int crosshairHalfSize{ 10 };
	int colorR{ 255 };
	int colorG{ 255 };
	int colorB{ 255 };
	bool isAlternativeShape{ false };
	int accel{ 1 };
	int maxVel{ 5 };
	std::vector<Enemy> enemies;
	int enemyAmount{ 5 };
	/********************************/
};