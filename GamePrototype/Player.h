#pragma once
#include "Square.h"
#include "Shade.h"
class Player : public Square
{
public:
    Player(float x, float y, float size);
    void Update(float elapsedSec, const Rectf& viewPort);
    void Draw(const Point2f& currMousePos) const;
    void Attack(Shade& shade);
    bool isInside(float cursorX, float cursorY) const;
    void ProcessMouseDownEvent(const Point2f& e);
    void ProcessMouseUpEvent(const Point2f& e);
private:
    int m_progressNewShade;
    int m_mistakes;
    Shade m_targetShade;

    Shade m_Shade;
    bool m_isPressed;
    Point2f m_OriginalPoint;
    Vector2f m_Velocity;

    const int m_NEEDED_KILLS;

    void NewTargetShade();
};