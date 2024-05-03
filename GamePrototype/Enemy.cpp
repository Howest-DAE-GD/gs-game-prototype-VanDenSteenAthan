#include "pch.h"
#include "Enemy.h"

Enemy::Enemy(float x, float y, Shade shade)
	: Square(x, y, shade.GetSize()), m_Shade{shade}, m_Velocity{(float)(rand() % 50 - 25), (float)(rand() % 50 - 25)}
{

}

void Enemy::Update(float elapsedSec, const Rectf& viewPort)
{
	m_Position.x += m_Shade.GetSpeed() * cos(m_Velocity.x * m_Velocity.y) * elapsedSec;
	m_Position.y += m_Shade.GetSpeed() * sin(m_Velocity.x * m_Velocity.y) * elapsedSec;
	if (m_Position.y < viewPort.bottom)
	{
		m_Velocity.x *= 0.8;
		m_Velocity.y *= -0.8;
		m_Position.y = 0.f;
	}
	if (m_Position.y + m_WIDTH > viewPort.height)
	{
		m_Velocity.x *= 0.8;
		m_Velocity.y *= -0.8;
		m_Position.y = viewPort.height - m_WIDTH;
	}
	if (m_Position.x < viewPort.left)
	{
		m_Velocity.x *= -0.8;
		m_Velocity.y *= 0.8;
		m_Position.x = 0.f;
	}
	if (m_Position.x + m_WIDTH > viewPort.width)
	{
		m_Velocity.x *= -0.8;
		m_Velocity.y *= 0.8;
		m_Position.x = viewPort.width - m_WIDTH;
	}
}

void Enemy::Draw() const
{
	DrawSquare(m_Shade.GetColor());
}

Shade& Enemy::GetShade()
{
	return m_Shade;
}