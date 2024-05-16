#include "pch.h"
#include "Player.h"
#include "Texture.h"

Player::Player(float x, float y, float size)
	: Square(x, y, size), m_Velocity{}, m_OriginalPoint{}, m_isPressed{}, m_Shade{ (ShadeType)(rand() % 4) },
	m_progressNewShade{}, m_lives{5}, m_TargetShade{ (ShadeType)0},
	m_NEEDED_KILLS{10}, m_score{0}
{
	m_txtTargetShade = nullptr; 
	m_txtLivesLeft = nullptr;
	m_txtScore = nullptr;
	NewTargetShade();
	UpdateTXT();
}

Player::~Player()
{
	delete m_txtTargetShade;
	delete m_txtLivesLeft;
	delete m_txtScore;
}

void Player::UpdateTXT()
{
	if(m_txtTargetShade != nullptr) delete m_txtTargetShade;
	m_txtTargetShade = new Texture("Target: " + m_TargetShade.GetShadeName() + "(" + std::to_string(m_progressNewShade) + "/" + std::to_string(m_NEEDED_KILLS) + ")", TXT_FONT_FILE, TXT_FONT_SIZE, Color4f{0.f, 0.f, 0.f, 1.f});

	if (m_txtLivesLeft != nullptr) delete m_txtLivesLeft;
	m_txtLivesLeft = new Texture("Lives left: " + std::to_string(m_lives), TXT_FONT_FILE, TXT_FONT_SIZE, Color4f{ 0.85f, 0.85f, 0.85f, 1.f });

	if (m_txtScore != nullptr) delete m_txtScore;
	m_txtScore = new Texture(IntToStringPadding(6,m_score), TXT_FONT_FILE, TXT_FONT_SIZE, Color4f{ 0.85f, 0.85f, 0.85f, 1.f });
}

std::string Player::IntToStringPadding(int length, int score)
{
	std::string str = std::to_string(score);
	int amount = length - str.length();
	if (length < str.length()) return "999999";
	for (int i{ 0 }; i < amount; ++i)
	{
		str = "0" + str;
	}
	return str;
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

	utils::SetColor(Color4f{ m_TargetShade.GetColor().r * 0.4f, m_TargetShade.GetColor().g * 0.4f, m_TargetShade.GetColor().b * 0.4f, 1.f });
	utils::FillRect(Rectf{ m_Position.x, m_Position.y, m_WIDTH, m_WIDTH * ((float)m_progressNewShade / (float)m_NEEDED_KILLS) });
	
	utils::SetColor(Color4f{ m_TargetShade.GetColor().r, m_TargetShade.GetColor().g, m_TargetShade.GetColor().b, ((float)m_progressNewShade / (float)m_NEEDED_KILLS) });
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

	utils::SetColor(Color4f{ m_TargetShade.GetColor().r, m_TargetShade.GetColor().g, m_TargetShade.GetColor().b, 0.4f });
	utils::FillRect(pointTarget, m_txtTargetShade->GetWidth() + 2 * PADDING_INSIDE, m_txtTargetShade->GetHeight() + 2 * PADDING_INSIDE);
	utils::SetColor(Color4f{0.f, 0.f, 0.f, 0.85f});
	utils::DrawRect(pointTarget, m_txtTargetShade->GetWidth() + 2 * PADDING_INSIDE, m_txtTargetShade->GetHeight() + 2 * PADDING_INSIDE, 2.f);
	m_txtTargetShade->Draw(Point2f{pointTarget.x + PADDING_INSIDE, pointTarget.y + PADDING_INSIDE});

	m_txtLivesLeft->Draw(Point2f{ pointTarget.x + PADDING_INSIDE, pointTarget.y + PADDING_INSIDE - 50.f });

	m_txtScore->Draw(Point2f{ viewPort.width - m_txtScore->GetWidth() - PADDING_OUTSIDE, viewPort.height - m_txtScore->GetHeight() - PADDING_OUTSIDE});
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

		if (extraVelocity.x < -200.f) extraVelocity.x = -200.f;
		if (extraVelocity.x > 200.f) extraVelocity.x = 200.f;
		if (extraVelocity.y < -200.f) extraVelocity.y = -200.f;
		if (extraVelocity.y > 200.f) extraVelocity.y = 200.f;


		m_Velocity.x = extraVelocity.x;
		m_Velocity.y = extraVelocity.y;
	}
	m_isPressed = false;
}

void Player::Attack(Shade& shade)
{
	if (shade == m_TargetShade)
	{
		++m_progressNewShade; 
		m_score += 10;
		if (m_progressNewShade == m_NEEDED_KILLS)
		{
			m_score += 500;
			m_progressNewShade = 0;
			m_Shade = shade;
			NewTargetShade();
		}
	}
	else
	{
		--m_lives;
	}
	UpdateTXT();
}

void Player::NewTargetShade()
{
	do
	{
		m_TargetShade = Shade{ (ShadeType)(rand() % 4) };
	} while (m_Shade == m_TargetShade);

	UpdateTXT();
}

int Player::GetLives() const
{
	return m_lives;
}