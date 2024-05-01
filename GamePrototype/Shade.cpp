#include "pch.h"
#include "Shade.h"

Shade::Shade(ShadeType type)
{
    switch (type) {
    case ShadeType::Aqua:
        m_Size = 45.0f;
        m_Speed = 55.0f;
        m_Color = Color4f{ 0.f, 1.f, 1.f, 1.f };
        break;
    case ShadeType::Granite:
        m_Size = 45.0f;
        m_Speed = 55.0f;
        m_Color = Color4f{ 0.38f, 0.252f, 0.207f, 1.f };
        break;
    case ShadeType::Yellow:
        m_Size = 45.0f;
        m_Speed = 85.0f;
        m_Color = Color4f{ 1.f, 1.f, 0.f, 1.f };
        break;
    case ShadeType::Viridian:
        m_Size = 35.0f;
        m_Speed = 55.0f;
        m_Color = Color4f{ 0.25f, 0.51f, 0.43f, 1.f };
        break;
    }
}

float Shade::getSize() const { return m_Size; }
float Shade::getSpeed() const { return m_Speed; }
Color4f Shade::getColor() const { return m_Color; }

bool Shade::operator==(const Shade& other) const
{
    return (m_Color.r == other.m_Color.r) &&
        (m_Color.g == other.m_Color.g) &&
        (m_Color.b == other.m_Color.b) &&
        (m_Color.a == other.m_Color.a);
}