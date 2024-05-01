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
    bool operator==(const Shade& other) const;

    float getSize() const;
    float getSpeed() const;
    Color4f getColor() const;

private:
    float m_Size;
    float m_Speed;
    Color4f m_Color;
};