#pragma once

struct Color4f;

enum class ShadeType
{
    Aqua,
    Granite,
    Yellow,
    Viridian
};

class Shade {
public:
    Shade(ShadeType type);

    bool operator=(const Shade& shade);
    bool operator==(const Shade& other) const;

    float GetSize() const;
    float GetSpeed() const;
    Color4f GetColor() const;
    ShadeType GetShadeType() const;
    std::string GetShadeName() const;

private:
    float m_Size;
    float m_Speed;
    Color4f m_Color;
    ShadeType m_ShadeType;
};