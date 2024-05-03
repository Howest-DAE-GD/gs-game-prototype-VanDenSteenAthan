#include "pch.h"
#include "Player.h"
#include "Texture.h"

Player::Player(float x, float y, float size)
	: Square(x, y, size), m_Velocity{}, m_OriginalPoint{}, m_isPressed{}, m_Shade{ (ShadeType)(rand() % 4) },
	m_progressNewShade{}, m_lives{5}, m_targetShade{ (ShadeType)0},
	m_NEEDED_KILLS{10}
{
	m_txtTargetShade = nullptr;
	NewTargetShade();
}

Player::~Player()
{
	delete m_txtTargetShade;
}

void Player::UpdateTXT()
{
	if(m_txtTargetShade != nullptr) delete m_txtTargetShade;
	m_txtTargetShade = new Texture("Target: " + m_targetShade.GetShadeName(), TXT_FONT_FILE, TXT_FONT_SIZE, Color4f{0.f, 0.f, 0.f, 1.f});
}

void Player::Update(float elapsedSec, const Rectf& viewPort)
{
	m_Position.x += m_Velocity.x * elapsedSec;
	m_Position.y += m_Velocity.y * elapsedSec;

	m_Velocity.x *= 0.99f;
	m_Velocity.y *= 0.99f;

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

void Player::Draw(const Point2f& currMousePos, const Rectf& viewPort) const
{
	DrawSquare(m_Shade.GetColor());

	utils::SetColor(Color4f{ m_targetShade.GetColor().r * 0.4f, m_targetShade.GetColor().g * 0.4f, m_targetShade.GetColor().b * 0.4f, 1.f });
	utils::FillRect(Rectf{ m_Position.x, m_Position.y, m_WIDTH, m_WIDTH * ((float)m_progressNewShade / (float)m_NEEDED_KILLS) });
	
	utils::SetColor(Color4f{ m_targetShade.GetColor().r, m_targetShade.GetColor().g, m_targetShade.GetColor().b, ((float)m_progressNewShade / (float)m_NEEDED_KILLS) });
	utils::FillRect(Rectf{ m_Position.x, m_Position.y, m_WIDTH, m_WIDTH * ((float)m_progressNewShade / (float)m_NEEDED_KILLS) });

	utils::SetColor(Color4f{ 0.f, 0.f, 0.f, 0.85f });
	utils::DrawRect(Rectf{ m_Position.x, m_Position.y, m_WIDTH, m_WIDTH }, 3.f);

	if (m_isPressed)
	{
		utils::SetColor(Color4f{ 0.75f, 0.8f, 0.8f, 0.55f });
		utils::FillEllipse(m_OriginalPoint, 8.f, 8.f);
		utils::DrawLine(m_OriginalPoint, currMousePos, 3.f);
	}

	DrawHUD(viewPort);
}

void Player::DrawHUD(const Rectf& viewPort) const
{
	const float PADDING_INSIDE = { 5.f };
	const float PADDING_OUTSIDE = { 15.f };
	Point2f pointTarget{ PADDING_INSIDE ,viewPort.height - m_txtTargetShade->GetHeight() - 2 * PADDING_INSIDE - PADDING_OUTSIDE };

	utils::SetColor(m_targetShade.GetColor());
	utils::FillRect(pointTarget, m_txtTargetShade->GetWidth() + 2 * PADDING_INSIDE, m_txtTargetShade->GetHeight() + 2 * PADDING_INSIDE);
	utils::SetColor(Color4f{0.f, 0.f, 0.f, 1.f});
	utils::DrawRect(pointTarget, m_txtTargetShade->GetWidth() + 2 * PADDING_INSIDE, m_txtTargetShade->GetHeight() + 2 * PADDING_INSIDE, 2.f);
	m_txtTargetShade->Draw(Point2f{pointTarget.x + PADDING_INSIDE, pointTarget.y + PADDING_INSIDE});
}

bool Player::isInside(float cursorX, float cursorY) const {
	return utils::IsPointInRect(Point2f{ cursorX, cursorY }, Rectf{ m_Position.x, m_Position.y, m_WIDTH, m_WIDTH });
}

void Player::ProcessMouseDownEvent(const Point2f& e){
	if (isInside(e.x, e.y))
	{
		m_isPressed = true; 
		m_OriginalPoint = Point2f{ e.x, e.y };
	}
}

void Player::ProcessMouseUpEvent(const Point2f& e) {
	if (m_isPressed)
	{
		Vector2f extraVelocity{ m_OriginalPoint.x - e.x, m_OriginalPoint.y - e.y };

		if (extraVelocity.x < -150.f) extraVelocity.x = -150.f;
		if (extraVelocity.x > 150.f) extraVelocity.x = 150.f;
		if (extraVelocity.y < -150.f) extraVelocity.y = -150.f;
		if (extraVelocity.y > 150.f) extraVelocity.y = 150.f;


		m_Velocity.x = extraVelocity.x;
		m_Velocity.y = extraVelocity.y;
	}
	m_isPressed = false;
}

void Player::Attack(Shade& shade)
{
	if (shade == m_targetShade)
	{
		++m_progressNewShade;
		if (m_progressNewShade == m_NEEDED_KILLS)
		{
			m_progressNewShade = 0;
			m_Shade = shade;
			NewTargetShade();
		}
	}
	else
	{
		if (shade.GetShadeType() == ShadeType::Granite) m_lives = 0;
		else --m_lives;
	}
}

void Player::NewTargetShade()
{
	do
	{
		m_targetShade = Shade{ (ShadeType)(rand() % 4) };
	} while (m_Shade == m_targetShade);

	UpdateTXT();
}

int Player::GetLives() const
{
	return m_lives;
}