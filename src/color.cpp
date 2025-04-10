#include "color.h"

namespace renderer {

const Color Color::Black{0, 0, 0};
const Color Color::Red{255, 0, 0};
const Color Color::Green{0, 255, 0};
const Color Color::Blue{0, 0, 255};
const Color Color::Yellow{255, 255, 0};
const Color Color::Magenta{255, 0, 255};
const Color Color::Cyan{0, 255, 255};
const Color Color::White{255, 255, 255};

Color darken(Color color, double factor) {
    assert((factor >= 0) && (factor <= 1) && "color darkening factor must be in [0, 1]");
    uint8_t dark_red = round(factor * color.red);
    uint8_t dark_green = round(factor * color.green);
    uint8_t dark_blue = round(factor * color.blue);
    return Color{dark_red, dark_green, dark_blue};
}

bool operator==(Color lhs, Color rhs) {
    return (lhs.red == rhs.red) && (lhs.blue == rhs.blue) && (lhs.green == rhs.green);
}

bool operator!=(Color lhs, Color rhs) {
    return !(lhs == rhs);
}

} // namespace renderer