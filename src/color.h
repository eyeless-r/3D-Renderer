#pragma once

#include "linalg.h"

namespace renderer {

struct Color {
    static const Color Black;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Yellow;
    static const Color Magenta;
    static const Color Cyan;
    static const Color White;

    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
};

Color darken(Color color, double factor);

bool operator==(Color lhs, Color rhs);
bool operator!=(Color lhs, Color rhs);

} // namespace renderer