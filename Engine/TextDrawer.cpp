#include "TextDrawer.h"
#include "Graphics.h"
#include <vector>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib") // Apparently this works to include a library instead of adding to the libpath in the IDE https://learn.microsoft.com/en-us/windows/win32/gdiplus/-gdiplus-drawing-a-line-use


void TextDrawer::drawNumber(Graphics& gfx, int number, int x, int y)
{
	// convert integer to array of digits - https://stackoverflow.com/a/15987731/3174659
	std::vector<int> digits;
	do
	{
		digits.push_back(number % 10);
		number /= 10;
	} while (number); // do-while so that if number is zero, we also print it
	std::reverse(digits.begin(), digits.end());

	int nextImageX = x;
	wchar_t* fileName = L"";
	for (auto digit : digits)
	{
		if (digit == 1)
			fileName = L"..\\img\\one.png";
		if (digit == 2)
			fileName = L"..\\img\\two.png";
		if (digit == 3)
			fileName = L"..\\img\\three.png";
		if (digit == 4)
			fileName = L"..\\img\\four.png";
		if (digit == 5)
			fileName = L"..\\img\\five.png";
		if (digit == 6)
			fileName = L"..\\img\\six.png";
		if (digit == 7)
			fileName = L"..\\img\\seven.png";
		if (digit == 8)
			fileName = L"..\\img\\eight.png";
		if (digit == 9)
			fileName = L"..\\img\\nine.png";
		if (digit == 0)
			fileName = L"..\\img\\zero.png";

		drawImage(gfx, fileName, nextImageX, y);

		nextImageX += 20;
	}
}

void TextDrawer::drawImage(Graphics& gfx, wchar_t* fileName, int x, int y)
{
	// variables to setup system to read image files pixel by pixel - adapted from https://forum.planetchili.net/viewtopic.php?f=3&t=925#p1011
	// initializing GDI for every draw (every frame) is probably not very efficient...
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	Gdiplus::Bitmap bitmap(fileName);
	Gdiplus::Color pixel;

	for (unsigned int yPixel = 0; yPixel < bitmap.GetHeight(); yPixel++)
	{
		for (unsigned int xPixel = 0; xPixel < bitmap.GetWidth(); xPixel++)
		{
			bitmap.GetPixel(xPixel, yPixel, &pixel);
			// don't draw alpha (transparent) pixels
			if (pixel.GetAlpha() != 0)
			{
				gfx.PutPixel(x + xPixel, y + yPixel, pixel.GetR(), pixel.GetG(), pixel.GetB());
			}
		}
	}
	// we should make this call to cleanup, but it program consume more CPU and doesnt seem to bring any advantage
	//Gdiplus::GdiplusShutdown(gdiplusToken);

}