#include "Food.h"

#include "TextDrawer.h"

void Food::UpdatePosition(MainWindow& wnd)
{
}

void Food::Draw(Graphics& gfx) const
{
	TextDrawer::drawImage(gfx, L"..\\img\\apple.png", x - halfsize, y - halfsize);

}
