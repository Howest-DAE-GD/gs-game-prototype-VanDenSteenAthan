#pragma once
#include "utils.h"
class Square {
public:
    Square(float x, float y, float size);
    Rectf GetRect() const;
protected:
    void DrawSquare(const Color4f& color) const;
    Point2f m_Position;
    const float m_WIDTH;
};