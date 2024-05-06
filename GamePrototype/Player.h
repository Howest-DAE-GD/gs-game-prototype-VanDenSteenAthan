#pragma once
#include "Square.h"
#include "Shade.h"
class Texture;
class Player : public Square
{
public:
    Player(float x, float y, float size);
    ~Player();

    void Update(float elapsedSec, const Rectf& viewPort);
    void Draw(const Point2f& currMousePos, const Rectf& viewPort) const;
    void Attack(Shade& shade);
    bool isInside(float cursorX, float cursorY) const;
    void ProcessMouseDownEvent(const Point2f& e);
    void ProcessMouseUpEvent(const Point2f& e);

    int GetLives() const;
private:
    int m_progressNewShade;
    int m_lives;
    Shade m_targetShade;

    Shade m_Shade;
    bool m_isPressed;
    Point2f m_OriginalPoint;
    Vector2f m_Velocity;

    const int m_NEEDED_KILLS;

    void NewTargetShade();
    void UpdateTXT();
    void DrawHUD(const Rectf& viewPort) const;

    Texture* m_txtTargetShade;
    Texture* m_txtLivesLeft;
    const int TXT_FONT_SIZE{ 24 };
    const std::string TXT_FONT_FILE{ "Painter-LxXg.ttf" };
};