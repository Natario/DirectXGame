#pragma once
#include "Actor.h"

class Food : public Actor
{
public:
    Food(int x, int y) :
        Actor(x, y)
    {};

    void UpdatePosition(MainWindow& wnd, bool isGameModeRunaway) override;
    void Draw(class Graphics& gfx) const override;
};

