#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "color.h"
#include "linalg.h"

namespace renderer {

static constexpr Color DefaultPixelColor = Colors::Black;

struct Pixel {

    Color color = DefaultPixelColor;
    double z = 2;
};

enum Height : uint32_t;
enum Width : uint32_t;

class Screen {
public:
    Screen(Height height, Width width);

    uint32_t get_height() const;
    uint32_t get_width() const;
    Pixel &operator()(int32_t x, int32_t y);
    const Pixel &operator()(int32_t x, int32_t y) const;
    void set_pixel_if_closer(int32_t x, int32_t y, const Pixel &pixel);
    std::vector<sf::Vertex> get_pixels() const;

private:
    using ScreenPixels = std::vector<Pixel>;

    uint32_t width_;
    ScreenPixels data_;
};

} // namespace renderer
