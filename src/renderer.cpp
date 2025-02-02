#include "renderer.h"

namespace renderer {

Renderer::Renderer(size_t height, size_t width) : screen_(Screen(height, width)) {
}

void Renderer::add_triangle(const Triangle& triangle, const Camera& camera) {
    Triangle transformed = camera.transform_triangle_coordinates(triangle);
    transformed.sort_vertices();
    double height = camera.get_height();
    double width = camera.get_width();
    assert(-EPS <= transformed.a.x && transformed.c.x <= width + EPS && "Triangle vertex is outside the frame");
    assert(-EPS <= transformed.a.y && transformed.a.y <= height + EPS && "Triangle vertex is outside the frame");
    assert(-EPS <= transformed.b.y && transformed.b.y <= height + EPS && "Triangle vertex is outside the frame");
    assert(-EPS <= transformed.c.y && transformed.c.y <= height + EPS && "Triangle vertex is outside the frame");
    assert(-EPS <= transformed.a.z && transformed.a.z <= 1 + EPS && "Triangle vertex is outside the frame");
    assert(-EPS <= transformed.b.z && transformed.b.z <= 1 + EPS && "Triangle vertex is outside the frame");
    assert(-EPS <= transformed.c.z && transformed.c.z <= 1 + EPS && "Triangle vertex is outside the frame");
    double height_step = height / screen_.get_height();
    double width_step = width / screen_.get_width();
    size_t left_x = static_cast<int>(ceil(transformed.a.x / width_step - 0.5));
    size_t right_x = static_cast<int>(floor(transformed.c.x / width_step - 0.5));
    double x = width_step * (0.5 + left_x);
    for (size_t screen_x = left_x; screen_x <= right_x; ++screen_x, x += width_step) {
        std::pair<double, double> lower_upper_y = transformed.get_lower_upper_y(x);
        size_t lower_y = static_cast<int>(ceil(lower_upper_y.first / height_step - 0.5));
        size_t upper_y = static_cast<int>(floor(lower_upper_y.second / height_step - 0.5));
        double y = height_step * (0.5 + lower_y);
        for (size_t screen_y = lower_y; screen_y <= upper_y; ++screen_y, y += height_step) {
            screen_.set_pixel(screen_x, screen_y, Pixel(triangle.color, transformed.get_z(x, y)));
        }
    }
}

void Renderer::display(Window& window) {
    size_t height = screen_.get_height();
    size_t width = screen_.get_width();
    std::vector<sf::Vertex> pixels;
    pixels.reserve(height * width);
    for (size_t x = 0; x < width; ++x) {
        for (size_t y = 0; y < height; ++y) {
            Color color = screen_.get_pixel_color(x, y);
            if (color != Color::Transparent) {
                pixels.push_back(sf::Vertex{sf::Vector2f(x, height - 1 - y), color});
            }
        }
    }
    window.draw(pixels.data(), pixels.size(), sf::PrimitiveType::Points);
}

}  // namespace renderer
