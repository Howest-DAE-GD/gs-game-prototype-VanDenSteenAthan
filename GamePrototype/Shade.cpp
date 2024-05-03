#include "pch.h"
#include "Shade.h"

Shade::Shade(ShadeType type)
    : m_ShadeType{ type }, m_Size{}, m_Speed{}, m_Color{}
{
    switch (type) {
    case ShadeType::Aqua:
        m_Size = 45.0f;
        m_Speed = 44.0f;
        m_Color = Color4f{ 0.f, 1.f, 1.f, 1.f };
        break;
    case ShadeType::Granite:
        m_Size = 45.0f;
        m_Speed = 44.0f;
        m_Color = Color4f{ 0.58f, 0.252f, 0.207f, 1.f };
        break;
    case ShadeType::Yellow:
        m_Size = 45.0f;
        m_Speed = 110.0f;
        m_Color = Color4f{ 1.f, 1.f, 0.f, 1.f };
        break;
    case ShadeType::Viridian:
        m_Size = 35.0f;
        m_Speed = 44.0f;
        m_Color = Color4f{ 0.25f, 0.51f, 0.43f, 1.f };
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
        case ShadeType::Granite:
            return "Granite";
            break;
        case ShadeType::Yellow:
            return "Yellow";
            break;
        case ShadeType::Viridian:
            return "Viridian";
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