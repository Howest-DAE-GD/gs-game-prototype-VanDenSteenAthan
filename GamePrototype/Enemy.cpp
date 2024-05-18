#include "pch.h"
#include "Enemy.h"
#include "Texture.h"

int Enemy::m_InstanceCount = 0;
Texture* Enemy::m_pSpritesheet = nullptr;

Enemy::Enemy(float x, float y)
	: Enemy(x, y, (ShadeType)(rand() % 4))
{
	
}

Enemy::Enemy(float x, float y, ShadeType type)
	: m_Velocity{ Vector2f{ (float)(rand() % 10 - 5), (float)(rand() % 10 - 5) }}, m_Shade{ type }
{
	SetSquare(x, y, m_Shade.GetSize());

	m_InstanceCount++;

	if (!m_pSpritesheet) {
		m_pSpritesheet = new Texture("target.png");
	}
}

Enemy::~Enemy()
{
	m_InstanceCount--;

	if (m_InstanceCount == 0 && m_pSpritesheet) {
		delete m_pSpritesheet;
		m_pSpritesheet = nullptr;
	}
}

void Enemy::Update(float elapsedSec, const Rectf& viewPort)
{
	m_Position.x += m_Shade.GetSpeed() * sin(m_Velocity.x) * elapsedSec;
	m_Position.y += m_Shade.GetSpeed() * sin(m_Velocity.y) * elapsedSec;

	if (m_Velocity.x == 0.f) m_Velocity.x = 5.f;
	if (m_Velocity.y == 0.f) m_Velocity.y = 5.f;
	
	bool check = false;

	if (m_Position.y < viewPort.bottom)
	{
		m_Velocity.y *= -1;
		m_Position.y = 0.f;
		check = true;
	}
	if (m_Position.y + m_WIDTH > viewPort.height)
	{
		m_Velocity.y *= -1;
		m_Position.y = viewPort.height - m_WIDTH;
		check = true;
	}
	if (m_Position.x < viewPort.left)
	{
		m_Velocity.x *= -1;
		m_Position.x = 0.f;
		check = true;
	}
	if (m_Position.x + m_WIDTH > viewPort.width)
	{
		m_Velocity.x *= -1;
		m_Position.x = viewPort.width - m_WIDTH;
		check = true;
	}

	if (check)
	{
		ChangeShade();
	}
}

void Enemy::ChangeShade()
{
	ShadeType newShade;
	do
	{
		newShade = (ShadeType)(rand() % 4);
	} while (m_Shade == newShade);

	if (m_Shade.GetShadeType() == ShadeType::Green)
	{
		if (m_Position.y > 100)
		{
			m_Position.y += Shade(ShadeType::Green).GetSize();
			m_Position.y -= Shade(ShadeType::Yellow).GetSize();
		}
		if (m_Position.x > 100)
		{
			m_Position.x += Shade(ShadeType::Green).GetSize();
			m_Position.x -= Shade(ShadeType::Yellow).GetSize();
		}
	}
	m_Shade = newShade;
	SetSquare(m_Position.x, m_Position.y, m_Shade.GetSize());
}

void Enemy::SetSquare(float x, float y, float size)
{
	m_Position = Point2f{ x, y };
	m_WIDTH = size;
}

void Enemy::Draw(const bool isTarget) const
{
	const Color4f rgba = m_Shade.GetColor();

	const float SCALAR = 0.8f;

	const float r = rgba.r * SCALAR;
	const float g = rgba.g * SCALAR;
	const float b = rgba.b * SCALAR;

	DrawSquare(m_Shade.GetColor(), Color4f{r, g, b, 1.f});

	if (isTarget)
	{
		m_pSpritesheet->Draw(Rectf{ m_Position.x, m_Position.y, m_WIDTH, m_WIDTH }, Rectf{ (m_pSpritesheet->GetWidth() / 4.f) * (int)m_Shade.GetShadeType(), 0.f, (m_pSpritesheet->GetWidth() / 4.f), m_pSpritesheet->GetHeight() });
	}
}

Shade& Enemy::GetShade()
{
	return m_Shade;
}