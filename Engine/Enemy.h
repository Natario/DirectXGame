#pragma once
class Enemy
{
	public:
		Enemy(int x, int y) : x{ x }, y{ y }, alive{ true } {};
		int x;
		int y;
		bool alive;
};

