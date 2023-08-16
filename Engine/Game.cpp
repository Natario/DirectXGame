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
	createRandomEnemies(++currentLevel);
	
	createRandomFood(currentLevel);
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
	
	// POSITION UPDATE
	// 
	// update position of player depending, possibly, on input
	player.UpdatePosition(wnd);

	// update position of enemies
	for (auto& enemy : enemies) {
		enemy.UpdatePosition(wnd);
	}
	


	// COLLISION DETECTION
	// 
	// detect if the middle of player (crosshair) is on top of any enemy
	for (auto& enemy : enemies) {
		if (isOverlapping(player, enemy) && enemy.isAlive)
		{
			// in mode runaway, if player hits an enemy, he dies, so restart level
			// in normal mode, if player hits spacebar or mouse button (shoots) while on top of an enemy, kill enemy
			if (isModeRunaway)
			{
				createRandomFood(currentLevel);
				createRandomEnemies(currentLevel);
				break;
			}
			else if(wnd.kbd.KeyIsPressed(VK_SPACE) || wnd.mouse.LeftIsPressed())
				enemy.isAlive = false;
		}
	}



	// LEVEL UP CONDITIONS
	// 
	// in mode runaway, increase level when player gets food,
	// in normal mode, increase level when there are no enemies alive
	if (isModeRunaway)
	{
		if (isOverlapping(player, food))
		{
			createRandomFood(++currentLevel);
			createRandomEnemies(currentLevel);
		}

	}
	else
	{
		int enemiesAlive = std::count_if(
			enemies.cbegin(),
			enemies.cend(),
			[](const auto& enemy) {
				return enemy.isAlive;
			}
		);
		if (enemiesAlive == 0)
			createRandomEnemies(++currentLevel);
	}



}

void Game::ComposeFrame()
{

	// draw enemies
	for (auto& enemy : enemies) {
		if(enemy.isAlive)
			enemy.Draw(gfx);
	}

	// draw food
	if(isModeRunaway)
		food.Draw(gfx);

	// draw player (after enemies so it appears on top of them)
	player.Draw(gfx);
	
	// draw level information
	TextDrawer::drawLevel(gfx, currentLevel, 20, 20);

}

bool Game::isOverlapping(const Player& player, const Actor& enemy) const
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

void Game::createRandomFood(int level)
{
	// create food in ranndom position
	std::random_device seed;
	std::mt19937 gen{ seed() };
	int maxHalfsize = 50; // we assume food is no larger than 50
	std::uniform_int_distribution<> distX{ maxHalfsize, Graphics::ScreenWidth - maxHalfsize - 1 };
	std::uniform_int_distribution<> distY{ maxHalfsize, Graphics::ScreenHeight - maxHalfsize - 1 };
	food.x = distX(gen);
	food.y = distY(gen);
}


