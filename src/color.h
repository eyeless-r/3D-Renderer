#pragma once

#include "linalg.h"

namespace renderer {

struct Color {
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
};

namespace Colors {

static constexpr Color Black{0, 0, 0};
static constexpr Color Red{255, 0, 0};
static constexpr Color Green{0, 255, 0};
static constexpr Color Blue{0, 0, 255};
static constexpr Color Yellow{255, 255, 0};
static constexpr Color Magenta{255, 0, 255};
static constexpr Color Cyan{0, 255, 255};
static constexpr Color White{255, 255, 255};

} // namespace Colors

Color darken(Color color, double factor);

bool operator==(Color lhs, Color rhs);
bool operator!=(Color lhs, Color rhs);

} // namespace renderer
