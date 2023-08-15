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
	// create enemies in random positions
	std::random_device seed;
	std::mt19937 gen{ seed() };
	int maxHalfsize = 50; // we assume enemies are no larger than 50
	for (int i = 0; i < enemyAmount; i++)
	{
		std::uniform_int_distribution<> distX{ maxHalfsize, Graphics::ScreenWidth - maxHalfsize - 1 };
		std::uniform_int_distribution<> distY{ maxHalfsize, Graphics::ScreenHeight - maxHalfsize - 1 };
		std::uniform_int_distribution<> distSpeed{ 1, 3 };
		enemies.push_back(Enemy{ distX(gen), distY(gen), distSpeed(gen), distSpeed(gen) });
	}
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
	// increase player speed in the direction of key press
	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		if(player.yVel - player.accel > -player.maxVel)
			player.yVel -= player.accel;
	}
	if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		if (player.xVel + player.accel < player.maxVel)
			player.xVel += player.accel;
	}
	if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		if (player.yVel + player.accel < player.maxVel)
			player.yVel += player.accel;
	}
	if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		if (player.xVel - player.accel > -player.maxVel)
			player.xVel -= player.accel;
	}
	
	// decellerate if no key pressed
	if (!wnd.kbd.KeyIsPressed(VK_UP) && player.yVel < 0)
		player.yVel += player.accel;
	if (!wnd.kbd.KeyIsPressed(VK_DOWN) && player.yVel > 0)
		player.yVel -= player.accel;
	if (!wnd.kbd.KeyIsPressed(VK_RIGHT) && player.xVel > 0)
		player.xVel -= player.accel;
	if (!wnd.kbd.KeyIsPressed(VK_LEFT) && player.xVel < 0)
		player.xVel += player.accel;
	
	// update position of player depending on speed only if new position is not outside screen, otherwise stop the movement
	if (player.canMoveHorizontally())
		player.x += player.xVel;
	else
		player.xVel = 0;
	if (player.canMoveVertically())
		player.y += player.yVel;
	else
		player.yVel = 0;

	// update position of enemies and make them bounce when they hit the screen edge
	for (auto& enemy : enemies) {
		if (enemy.canMoveHorizontally())
			enemy.x += enemy.xVel;
		else
			enemy.xVel = -enemy.xVel;
		if (enemy.canMoveVertically())
			enemy.y += enemy.yVel;
		else
			enemy.yVel = -enemy.yVel;
	}
	
	// detect colision of player with enemy
	bool isColliding = false;
	for (auto& enemy : enemies) {
		if (isOverlapping(player, enemy) && enemy.isAlive)
		{
			isColliding = true;
			if(wnd.kbd.KeyIsPressed(VK_SPACE))
				enemy.isAlive = false;
		}
	}
	// if colliding with an enemy, change color to red
	if(isColliding)
	{
		player.colorR = 255;
		player.colorG = 0;
		player.colorB = 0;
	}
	else
	{
		player.colorR = 255;
		player.colorG = 255;
		player.colorB = 255;
	}

}

void Game::ComposeFrame()
{

	// draw player
	player.Draw(gfx);
	
	// draw enemies
	for (auto& enemy : enemies) {
		if(enemy.isAlive)
			enemy.Draw(gfx);
	}
}

bool Game::isOverlapping(Player player, Enemy enemy)
{
	return (player.x <= enemy.x + enemy.halfsize) && (player.x >= enemy.x - enemy.halfsize) && (player.y <= enemy.y + enemy.halfsize) && (player.y >= enemy.y - enemy.halfsize);
}

