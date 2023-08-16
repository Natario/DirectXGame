#pragma once
class TextDrawer
{
public:
	static void drawLevel(class Graphics& gfx, int level, int x, int y);
	static void drawImage(class Graphics& gfx, wchar_t* fileName, int x, int y);
};

