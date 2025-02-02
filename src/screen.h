#include <vector>

#include "basics.h"

namespace renderer {
struct Pixel {
    Pixel(Color color = Color::Transparent, double z = 0);

    Color color;
    double z;
};

class Screen {
public:
    Screen(size_t height, size_t width);

    size_t get_height() const;

    size_t get_width() const;

    Color get_pixel_color(size_t x, size_t y) const;

    void set_pixel(size_t x, size_t y, const Pixel& pixel);

private:
    using ScreenPixels = std::vector<Pixel>;

    size_t screen_height_;
    size_t screen_width_;
    ScreenPixels data_;
};
}  // namespace renderer
