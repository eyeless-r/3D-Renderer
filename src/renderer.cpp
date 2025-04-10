#include "renderer.h"
// #include <cmath>

namespace renderer {

Renderer::Renderer(Height height, Width width) : height_(height), width_(width) {
}

void Renderer::draw_screen_triangle(const ScreenTriangle &triangle, Screen &screen) const {
    assert(-kEps <= triangle.get_first_point_by_x().z && "Triangle vertex is in front of front plane");
    assert(-kEps <= triangle.get_second_point_by_x().z && "Triangle vertex is in front of front plane");
    assert(-kEps <= triangle.get_third_point_by_x().z && "Triangle vertex is in front of front plane");

    int32_t screen_height = screen.get_height();
    int32_t screen_width = screen.get_height();
    int32_t left_x = std::max(triangle.get_first_point_by_x().x, 0);
    int32_t right_x = std::min(triangle.get_third_point_by_x().x, screen_width - 1);
    for (int32_t x = left_x; x <= right_x; ++x) {
        ScreenTriangle::LowerUpperY lower_upper_y = triangle.get_lower_upper_y(x);
        int32_t lower_y = std::max(lower_upper_y.lower_y, 0);
        int32_t upper_y = std::min(lower_upper_y.upper_y, screen_height - 1);
        for (int32_t y = lower_y; y <= upper_y; ++y) {
            double z = triangle.get_z(x, y);
            if (z <= 1) {
                screen.set_pixel_if_closer(x, y, Pixel{triangle.triangle_color, z});
            }
        }
    }
}

void Renderer::draw_triangle(const Triangle &triangle, Screen &screen, const Camera &camera, const Light &light) const {
    double height = camera.get_height();
    double width = camera.get_width();
    double height_step = screen.get_height() / height;
    double width_step = screen.get_width() / width;
    Color darkened_color = light.darken_triangle_color(triangle);
    auto transformed_triangles = camera.clip_transform_triangle(triangle);
    for (const auto &transformed_triangle : transformed_triangles) {
        draw_screen_triangle(ScreenTriangle(transformed_triangle, darkened_color, height_step, width_step), screen);
    }
}

Screen Renderer::render(const World &world_, const Camera &camera, const Light &light) const {
    Screen screen(height_, width_);
    for (const auto &object_ptr : world_.objects) {
        for (const auto &triangle : object_ptr->get_triangles()) {
            draw_triangle(triangle, screen, camera, light);
        }
    }
    return screen;
}

} // namespace renderer
