#include "pch.h"
#include "Shade.h"

Shade::Shade(ShadeType type)
    : m_ShadeType{ type }, m_Size{}, m_Speed{}, m_Color{}
{
    switch (type) {
    case ShadeType::Aqua:
        m_Size = 45.0f;
        m_Speed = 72.0f;
        m_Color = Color4f{ 0.2f, 0.9f, 0.9f, 1.f };
        break;
    case ShadeType::Green:
        m_Size = 35.0f;
        m_Speed = 72.0f;
        m_Color = Color4f{ 0.35f, 0.81f, 0.53f, 1.f };
        break;
    case ShadeType::Red:
        m_Size = 45.0f;
        m_Speed = 72.0f;
        m_Color = Color4f{ 0.68f, 0.322f, 0.287f, 1.f };
        break;
    case ShadeType::Yellow:
        m_Size = 45.0f;
        m_Speed = 102.0f;
        m_Color = Color4f{ 0.9f, 0.9f, 0.2f, 1.f };
        break;
    }
}

float Shade::GetSize() const { return m_Size; }
float Shade::GetSpeed() const { return m_Speed; }
Color4f Shade::GetColor() const { return m_Color; }
ShadeType Shade::GetShadeType() const{ return m_ShadeType; }
std::string Shade::GetShadeName() const
{
    switch (m_ShadeType)
    {
        case ShadeType::Aqua:
            return "Aqua";
            break;
        case ShadeType::Green:
            return "Green";
            break;
        case ShadeType::Red:
            return "Red";
            break;
        case ShadeType::Yellow:
            return "Yellow";
            break;
    }
}

bool Shade::operator=(const Shade& shade)
{
    m_ShadeType = shade.GetShadeType();
    m_Size = shade.GetSize();
    m_Speed = shade.GetSpeed();
    m_Color = shade.GetColor();
    return this;
}

bool Shade::operator==(const Shade& other) const
{
    return (m_Color.r == other.m_Color.r) &&
        (m_Color.g == other.m_Color.g) &&
        (m_Color.b == other.m_Color.b) &&
        (m_Color.a == other.m_Color.a);
}