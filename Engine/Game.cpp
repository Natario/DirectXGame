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
	// delta time: calculate how much time the last frame took and then start counting how much time this frame will take
	std::chrono::steady_clock::time_point currentFrameTimestamp = std::chrono::steady_clock::now();
	std::chrono::duration<float> frameTime = currentFrameTimestamp - previousFrameTimestamp;
	float deltaTime = frameTime.count();
	previousFrameTimestamp = std::chrono::steady_clock::now();

	
	if (isStartMenu)
	{
		// start menu looks like it has buttons, so let user use the mouse to click on them as well
		// TODO if we change the menu image, we have to adapt the mouse clicking coordinates
		if ((wnd.kbd.KeyIsPressed('1')) ||
			(wnd.mouse.LeftIsPressed() && (wnd.mouse.GetPosX() > 250) && (wnd.mouse.GetPosX() < 550) && (wnd.mouse.GetPosY() > 205) && (wnd.mouse.GetPosY() < 280)))
		{
			isGameModeRunaway = false;
			isStartMenu = false;
		}
		if ((wnd.kbd.KeyIsPressed('2')) ||
			(wnd.mouse.LeftIsPressed() && (wnd.mouse.GetPosX() > 250) && (wnd.mouse.GetPosX() < 550) && (wnd.mouse.GetPosY() > 300) && (wnd.mouse.GetPosY() < 370)))
		{
			isGameModeRunaway = true;
			isStartMenu = false;
		}

	}
	else if (!isGameOver)
	{
		// POSITION UPDATE
		// 
		// update position of player depending, possibly, on input
		player.UpdatePosition(wnd, isGameModeRunaway, deltaTime);

		// update position of enemies
		for (auto& enemy : enemies) {
			enemy.UpdatePosition(wnd, isGameModeRunaway, deltaTime);
		}



		// COLLISION DETECTION
		// 
		// detect if the center of player is on top of any enemy
		for (auto& enemy : enemies) {
			if (isOverlappingCenter(player, enemy) && enemy.isAlive)
			{
				// in mode runaway, if player hits an enemy after the grace period, he dies, so restart level
				// in normal mode, if player hits spacebar or mouse button (shoots) while on top of an enemy, kill enemy
				if (isGameModeRunaway)
				{
					if (gracePeriodTimer <= 0)
					{
						gameoverSound.Play(1,2);
						isGameOver = true;
					}
				}
				else if (ammo > 0 && reloadingTimer == 0 && (wnd.kbd.KeyIsPressed(VK_SPACE) || wnd.mouse.LeftIsPressed()))
				{
					enemy.isAlive = false;
				}
			}
		}



		// LEVEL UP CONDITIONS
		// 
		// in mode runaway, increase level when player gets food,
		// in normal mode, increase level when there are no enemies alive
		if (isGameModeRunaway)
		{
			// in mode runaway, let player touch the food just with the tip (in shooting mode, the center of the crosshair needs to overlap the enemy so we use isOverlappingCenter)
			if (gracePeriodTimer <= 0 && isOverlapping(player, food))
			{
				chewSound.Play(rng);
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
				ammo = currentLevel + 5;
			}
		}


		// TIMERS
		// 
		// during grace period, color player green and decrement timer until it reaches zero
		if (isGameModeRunaway && gracePeriodTimer > 0)
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
		if (!isGameModeRunaway && (wnd.kbd.KeyIsPressed(VK_SPACE) || wnd.mouse.LeftIsPressed()))
		{
			// if he can shoot, play appropriate sound and reset timer (either to know when to shoot again or to play unloaded sound at an interval - if we dont use a timer the sound plays everyframe)
			if (reloadingTimer == 0)
			{
				// if he has ammo, decrease it 
				if (ammo > 0) {
					ammo--;
					shotSound.Play(rng);
				}
				else
				{
					unloadedSound.Play(rng);
				}
				reloadingTimer = reloadingTime;
			}
		}
		if (reloadingTimer > 0)
		{
			reloadingTimer--;
		}
	}


}

void Game::ComposeFrame()
{

	if (isStartMenu)
	{
		TextDrawer::drawImage(gfx, L"img\\startmenu.png", 0, 0);
	}
	else if(!isGameOver)
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
		TextDrawer::drawImage(gfx, L"img\\level.png", 20, 20);
		TextDrawer::drawNumber(gfx, currentLevel, 100, 20);
		if (!isGameModeRunaway)
		{
			TextDrawer::drawImage(gfx, L"img\\ammo.png", 400, 20);
			TextDrawer::drawNumber(gfx, ammo, 480, 20);
		}
	}
	else
	{
		TextDrawer::drawImage(gfx, L"img\\gameover.png", Graphics::ScreenWidth / 2 - 100, Graphics::ScreenHeight / 2 - 100);
	}


	// draw player speed for debugging
	//TextDrawer::drawNumber(gfx, player.xVel, 50, 300);
	//TextDrawer::drawNumber(gfx, player.yVel, 50, 350);
	
}

bool Game::isOverlapping(const Player& player, const Actor& enemy) const
{
	return (player.x - player.halfsize <= enemy.x + enemy.halfsize) && (player.x + player.halfsize >= enemy.x - enemy.halfsize) &&
			(player.y - player.halfsize <= enemy.y + enemy.halfsize) && (player.y + player.halfsize >= enemy.y - enemy.halfsize);
}

bool Game::isOverlappingCenter(const Player& player, const Actor& enemy) const
{
	return (player.x <= enemy.x + enemy.halfsize) && (player.x >= enemy.x - enemy.halfsize) &&
			(player.y <= enemy.y + enemy.halfsize) && (player.y >= enemy.y - enemy.halfsize);
}

void Game::createRandomEnemies(int level)
{
	// create enemies in random positions with random speeds but increase their amount and speed with each level
	float maxHalfsize = 50; // we assume enemies are no larger than 50
	int maxEnemies{ level };
	float minEnemySpeed{ 100 };
	float maxEnemySpeed{ 300 };
	if (isGameModeRunaway)
	{
		maxEnemies = 20; // in runaway mode, limit the amount of enemies on screen so there is space to actually run away
		maxEnemySpeed = 200; // in runaway mode, make enemies a bit slower than in shooting mode, otherwise it's too hard
	}
	enemies.clear();
	for (int i = 0; i < std::min(level, maxEnemies) ; i++)
	{
		std::uniform_real_distribution<float> distX{ maxHalfsize, Graphics::ScreenWidth - maxHalfsize - 1 };
		std::uniform_real_distribution<float> distY{ maxHalfsize, Graphics::ScreenHeight - maxHalfsize - 1 };
		// don't increase speed too much because it causes motion sickness (max(min()) is like clamp() - https://stackoverflow.com/a/9324086/3174659)
		std::uniform_real_distribution<float> distSpeed{ minEnemySpeed, std::max(minEnemySpeed, std::min(level*100.0f, maxEnemySpeed)) };
		// for every enemy, change sign of speeds so they dont all move in the same direction
		if(i % 4 == 0)
			enemies.push_back(Enemy{ distX(rng), distY(rng), distSpeed(rng), distSpeed(rng) });
		if (i % 4 == 1)
			enemies.push_back(Enemy{ distX(rng), distY(rng), -distSpeed(rng), distSpeed(rng) });
		if (i % 4 == 2)
			enemies.push_back(Enemy{ distX(rng), distY(rng), distSpeed(rng), -distSpeed(rng) });
		if (i % 4 == 3)
			enemies.push_back(Enemy{ distX(rng), distY(rng), -distSpeed(rng), -distSpeed(rng) });
	}
}

void Game::createRandomFood(int level)
{
	// create food in ranndom position
	float maxHalfsize = 50; // we assume food is no larger than 50
	std::uniform_real_distribution<float> distX{ maxHalfsize, Graphics::ScreenWidth - maxHalfsize - 1 };
	std::uniform_real_distribution<float> distY{ maxHalfsize, Graphics::ScreenHeight - maxHalfsize - 1 };
	food.x = distX(rng);
	food.y = distY(rng);
}


