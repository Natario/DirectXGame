#pragma once
class TextDrawer
{
public:
	static void drawNumber(class Graphics& gfx, int level, int x, int y);
	static void drawImage(class Graphics& gfx, wchar_t* fileName, int x, int y);
};

