#pragma once
#include "Square.h"
#include "Shade.h"
class Enemy : public Square
{
public:
    explicit Enemy(float x, float y);
    void Update(float elapsedSec, const Rectf& viewPort);
    void Draw() const;

    Shade& GetShade();
private:
    explicit Enemy(float x, float y, ShadeType type);

    void ChangeShade();
    void SetSquare(float x, float y, float size);

    Shade m_Shade;
    Vector2f m_Velocity;
};