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
#include "Player.h"
#include "Enemy.h"
#include "Food.h"
#include "TextDrawer.h"

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
	bool isOverlapping(const Player& player, const Actor& enemy) const;
	void createRandomEnemies(int level);
	void createRandomFood(int level);
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	Player player{ Graphics::ScreenWidth / 2, Graphics::ScreenHeight / 2 };
	std::vector<Enemy> enemies{};
	int currentLevel{ 0 };
	Food food{ Graphics::ScreenWidth / 2, Graphics::ScreenHeight / 2 };
	bool isGameModeRunaway{ false }; // alternative game mode where player has to run away from enemies instead of shooting them. also has to eat food to level up
	bool isGameOver{ false };
	bool isStartMenu{ true };
	int gracePeriodTime{ 60 * 1 }; // 1 second of grace period (because the timer is decremented every frame i.e. 60 times per second - TODO adapt this to higher FPS rates!
	int gracePeriodTimer{gracePeriodTime}; // give player a grace period when he levels up because enemies might spawn on top of him and he needs to move away
	int ammo{ 5 };
	int reloadingTime{30}; // half a frame in 60FPS - TODO adapt this to higher FPS rates!
	int reloadingTimer{reloadingTime};
	/********************************/
};