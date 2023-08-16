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
	// detect if the middle of player (crosshair) is on top of any enemy (after a cooldown period)
	if (gracePeriodTimer <= 0)
	{
		for (auto& enemy : enemies) {
			if (isOverlapping(player, enemy) && enemy.isAlive)
			{
				// in mode runaway, if player hits an enemy, he dies, so restart level
				// in normal mode, if player hits spacebar or mouse button (shoots) while on top of an enemy, kill enemy
				if (isGameModeRunaway)
				{
					isGameOver = true;
					break;
				}
				else if (ammo > 0 && reloadingTimer == 0 && (wnd.kbd.KeyIsPressed(VK_SPACE) || wnd.mouse.LeftIsPressed()))
				{
					enemy.isAlive = false;
				}
			}
		}
	}



	// LEVEL UP CONDITIONS
	// 
	// in mode runaway, increase level when player gets food,
	// in normal mode, increase level when there are no enemies alive
	if (isGameModeRunaway)
	{
		if (isOverlapping(player, food))
		{
			createRandomFood(++currentLevel);
			createRandomEnemies(currentLevel);
			gracePeriodTimer = gracePeriodTime;
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
		{
			createRandomEnemies(++currentLevel);
			gracePeriodTimer = gracePeriodTime;
			ammo = currentLevel + 5;
		}
	}


	// during grace period, color player green and decrement timer until it reaches zero
	if (gracePeriodTimer > 0)
	{
		player.colorR = 0;
		player.colorG = 255;
		player.colorB = 0; 
		gracePeriodTimer--;
	}
	else
	{
		player.colorR = 255;
		player.colorG = 255;
		player.colorB = 255;
	}


	// if the user is continually shooting, decrease ammo every x frames (reloadingTime) so that he doesnt just leave the button pressed
	if (ammo > 0 && reloadingTimer == 0 && (wnd.kbd.KeyIsPressed(VK_SPACE) || wnd.mouse.LeftIsPressed()))
	{
		ammo--;
		reloadingTimer = reloadingTime;
	}
	if (reloadingTimer > 0)
	{
		reloadingTimer--;
	}


}

void Game::ComposeFrame()
{

	if (!isGameOver)
	{
		// draw enemies
		for (auto& enemy : enemies) {
			if(isGameModeRunaway)
				enemy.DrawAlternative(gfx);
			else if (enemy.isAlive)
				enemy.Draw(gfx);
		}

		// draw food
		if (isGameModeRunaway)
			food.Draw(gfx);

		// draw player (after enemies so it appears on top of them)
		if (isGameModeRunaway)
			player.DrawAlternative(gfx, gracePeriodTimer > 0);
		else
			player.Draw(gfx);

		// draw level and ammo information
		TextDrawer::drawImage(gfx, L"..\\img\\level.png", 20, 20);
		TextDrawer::drawNumber(gfx, currentLevel, 100, 20);
		if (!isGameModeRunaway)
		{
			TextDrawer::drawImage(gfx, L"..\\img\\ammo.png", 400, 20);
			TextDrawer::drawNumber(gfx, ammo, 480, 20);
		}
	}
	else
	{
		TextDrawer::drawImage(gfx, L"..\\img\\gameover.png", Graphics::ScreenWidth / 2 - 100, Graphics::ScreenHeight / 2 - 100);
	}

}

bool Game::isOverlapping(const Player& player, const Actor& enemy) const
{
	return (player.x <= enemy.x + enemy.halfsize) && (player.x >= enemy.x - enemy.halfsize) && (player.y <= enemy.y + enemy.halfsize) && (player.y >= enemy.y - enemy.halfsize);
}

void Game::createRandomEnemies(int level)
{
	// create enemies in random positions with random speeds but increase their amount and speed with each level
	std::random_device seed;
	std::mt19937 gen{ seed() };
	int maxHalfsize = 50; // we assume enemies are no larger than 50
	int maxEnemies{ level };
	if(isGameModeRunaway)
		maxEnemies = 25; // limit the amount of enemies on screen so there is space to actually run away
	else
	enemies.clear();
	for (int i = 0; i < std::min(level, maxEnemies) ; i++)
	{
		std::uniform_int_distribution<> distX{ maxHalfsize, Graphics::ScreenWidth - maxHalfsize - 1 };
		std::uniform_int_distribution<> distY{ maxHalfsize, Graphics::ScreenHeight - maxHalfsize - 1 };
		// don't increase speed too much because it causes motion sickness (max(min()) is like clamp() - https://stackoverflow.com/a/9324086/3174659)
		std::uniform_int_distribution<> distSpeed{ 1, std::max(1, std::min(level, 4)) };
		// for every enemy, change sign of speeds so they dont all move in the same direction
		if(i % 4 == 0)
			enemies.push_back(Enemy{ distX(gen), distY(gen), distSpeed(gen), distSpeed(gen) });
		if (i % 4 == 1)
			enemies.push_back(Enemy{ distX(gen), distY(gen), -distSpeed(gen), distSpeed(gen) });
		if (i % 4 == 2)
			enemies.push_back(Enemy{ distX(gen), distY(gen), distSpeed(gen), -distSpeed(gen) });
		if (i % 4 == 3)
			enemies.push_back(Enemy{ distX(gen), distY(gen), -distSpeed(gen), -distSpeed(gen) });
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


