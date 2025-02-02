#include "screen.h"

#include "basics.h"

namespace renderer {
Pixel::Pixel(Color color, double z) : color(color), z(z){};

Screen::Screen(size_t height, size_t width)
    : screen_height_(height), screen_width_(width), data_(std::vector(height * width, Pixel())){};

size_t Screen::get_height() const {
    return screen_height_;
}

size_t Screen::get_width() const {
    return screen_width_;
}

Color Screen::get_pixel_color(size_t x, size_t y) const {
    return data_[x * screen_width_ + y].color;
}

void Screen::set_pixel(size_t x, size_t y, const Pixel& pixel) {  // to do: transparency
    if (data_[x * screen_width_ + y].color == Color::Transparent || data_[x * screen_width_ + y].z > pixel.z) {
        data_[x * screen_width_ + y] = pixel;
    }
}
}  // namespace renderer
