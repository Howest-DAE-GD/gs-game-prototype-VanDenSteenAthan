#pragma once
#include "Square.h"
#include "Shade.h"
class Enemy : public Square
{
public:
    Enemy(float x, float y, Shade shade);
    void Update(float elapsedSec, const Rectf& viewPort);
    void Draw() const;
    Shade& GetShade();
private:
    Shade m_Shade;
    Vector2f m_Velocity;
};