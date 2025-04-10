#include "screen.h"

namespace renderer {

Screen::Screen(Height height, Width width) : width_(width), data_(height * width) {
    assert(height > 0 && "Screen height can not be 0");
    assert(width > 0 && "Screen width can not be 0");
}

uint32_t Screen::get_height() const {
    return data_.size() / width_;
}

uint32_t Screen::get_width() const {
    return width_;
}

Pixel &Screen::operator()(int32_t x, int32_t y) {
    if ((x >= get_height()) || (y >= width_)) {
        throw std::invalid_argument("Screen index is out of range");
    }
    return data_[x * width_ + y];
}
const Pixel &Screen::operator()(int32_t x, int32_t y) const {
    if ((x < 0) || (x >= get_height()) || (y < 0) || (y >= width_)) {
        throw std::invalid_argument("Screen index is out of range");
    }
    return data_[x * width_ + y];
}

void Screen::set_pixel_if_closer(int32_t x, int32_t y, const Pixel &pixel) {
    if ((x < 0) || (x >= get_height()) || (y < 0) || (y >= width_)) {
        throw std::invalid_argument("Screen index is out of range");
    }
    if ((*this)(x, y).z > pixel.z) {
        (*this)(x, y) = pixel;
    }
}

std::vector<sf::Vertex> Screen::get_pixels() const {
    uint32_t height = get_height();
    std::vector<sf::Vertex> pixels;
    pixels.reserve(height * width_);
    for (int32_t pixel_index = 0; pixel_index < data_.size(); ++pixel_index) {
        int32_t x = pixel_index / width_;
        int32_t y = pixel_index % width_;
        Color color = data_[pixel_index].color;
        if (color == default_pixel_color) {
            continue;
        }
        pixels.push_back(sf::Vertex{sf::Vector2f(x, height - 1 - y), sf::Color(color.red, color.green, color.blue)});
    }
    return pixels;
}

} // namespace renderer
