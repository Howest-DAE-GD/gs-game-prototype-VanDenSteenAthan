#include "pch.h"
#include "Square.h"

Square::Square(float x, float y, float size)
	: m_Position{ Point2f{ x, y } }, m_WIDTH{size}
{

}

Rectf Square::GetRect() const
{
	return Rectf{ m_Position.x, m_Position.y, m_WIDTH, m_WIDTH };
}

void Square::DrawSquare(const Color4f& color) const
{
	utils::SetColor(color);
	utils::FillRect(Rectf{ m_Position.x, m_Position.y, m_WIDTH, m_WIDTH });
}