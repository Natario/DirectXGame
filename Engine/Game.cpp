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
#include <algorithm>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	createRandomEnemies(nextLevel++);
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
	
	// update position of player depending, possibly, on input
	player.UpdatePosition(wnd);

	// update position of enemies
	for (auto& enemy : enemies) {
		enemy.UpdatePosition(wnd);
	}
	
	// detect if the middle of player (crosshair) is on top of any enemy
	bool isColliding = false;
	for (auto& enemy : enemies) {
		if (isOverlapping(player, enemy) && enemy.isAlive)
		{
			isColliding = true;
			// if player hits spacebar or mouse button (shoots) while on top of an enemy, kill enemy
			if(wnd.kbd.KeyIsPressed(VK_SPACE) || wnd.mouse.LeftIsPressed())
				enemy.isAlive = false;
		}
	}
	// if player is colliding with (targeting) an enemy, change color to red
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

	// count number of enemies alive and if there are none go to next level 
	int enemiesAlive = std::count_if(
		enemies.cbegin(),
		enemies.cend(),
		[](const auto& enemy) {
			return enemy.isAlive;
		}
	);
	if (enemiesAlive == 0)
		createRandomEnemies(nextLevel++);

	textDrawer.drawLevelText(gfx, 20, 20);
	if (nextLevel == 2)
		textDrawer.drawOneText(gfx, 100, 20);
	if (nextLevel == 3)
		textDrawer.drawTwoText(gfx, 100, 20);
	if (nextLevel == 4)
		textDrawer.drawThreeText(gfx, 100, 20);
	if (nextLevel == 5)
		textDrawer.drawFourText(gfx, 100, 20);
	if (nextLevel == 6)
		textDrawer.drawFiveText(gfx, 100, 20);
	if (nextLevel == 7)
		textDrawer.drawSixText(gfx, 100, 20);
	if (nextLevel == 8)
		textDrawer.drawSevenText(gfx, 100, 20);
	if (nextLevel == 9)
		textDrawer.drawEightText(gfx, 100, 20);
	if (nextLevel == 10)
		textDrawer.drawNineText(gfx, 100, 20);
	if (nextLevel == 11)
	{
		textDrawer.drawOneText(gfx, 100, 20);
		textDrawer.drawZeroText(gfx, 120, 20);
	}
	//TODO: need to find a more reusable way to draw all possible levels

}

void Game::ComposeFrame()
{

	// draw enemies
	for (auto& enemy : enemies) {
		if(enemy.isAlive)
			enemy.Draw(gfx);
	}

	// draw player (after enemies so it appears on top of them)
	player.Draw(gfx);

}

bool Game::isOverlapping(const Player& player, const Enemy& enemy) const
{
	return (player.x <= enemy.x + enemy.halfsize) && (player.x >= enemy.x - enemy.halfsize) && (player.y <= enemy.y + enemy.halfsize) && (player.y >= enemy.y - enemy.halfsize);
}

void Game::createRandomEnemies(int level)
{
	// create enemies in random positions with random speeds but increase amount and speed with level
	std::random_device seed;
	std::mt19937 gen{ seed() };
	int maxHalfsize = 50; // we assume enemies are no larger than 50
	enemies.clear();
	for (int i = 0; i < std::min(level, 10) ; i++)
	{
		std::uniform_int_distribution<> distX{ maxHalfsize, Graphics::ScreenWidth - maxHalfsize - 1 };
		std::uniform_int_distribution<> distY{ maxHalfsize, Graphics::ScreenHeight - maxHalfsize - 1 };
		std::uniform_int_distribution<> distSpeed{ 1, std::max(1, std::min(level, 4)) }; // don't increase speed too much because it causes motion sickness (max(min()) is like clamp() - https://stackoverflow.com/a/9324086/3174659)
		enemies.push_back(Enemy{ distX(gen), distY(gen), distSpeed(gen), distSpeed(gen) });
	}
}


