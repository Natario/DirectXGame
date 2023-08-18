#pragma once
#include "Actor.h"

class Food : public Actor
{
public:
    Food(float x, float y) :
        Actor(x, y)
    {};

    void UpdatePosition(MainWindow& wnd, bool isGameModeRunaway, float deltaTime) override;
    void Draw(class Graphics& gfx) const override;
};

