#include "Food.h"

#include "TextDrawer.h"

void Food::UpdatePosition(MainWindow& wnd, bool isGameModeRunaway, float deltaTime)
{
}

void Food::Draw(Graphics& gfx) const
{
	TextDrawer::drawImage(gfx, L"img\\apple.png", int(x - halfsize), int(y - halfsize));

}
