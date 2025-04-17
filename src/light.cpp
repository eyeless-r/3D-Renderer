#include "light.h"

namespace renderer {

Light::Light(double intensity, Vector3 direction) : intensity_(std::max(std::min(intensity, 1.0), 0.0)) {
    assert((direction != Vector3{0, 0, 0}) && "Light direction can not be zero vector");
    direction_ = direction.normalized();
}

void Light::rotate_light(Axis axis, double angle) {
    double cosine = cos(angle);
    double sinus = sin(angle);
    switch (axis) {
    case Axis::X:
        direction_ =
            Matrix3{
                {1, 0,      0     },
                {0, cosine, -sinus},
                {0, sinus,  cosine},
        } *
            direction_;
        return;
    case Axis::Y:
        direction_ =
            Matrix3{
                {cosine, 0, sinus },
                {0,      1, 0     },
                {-sinus, 0, cosine}
        } *
            direction_;
        return;
    default:
        direction_ =
            Matrix3{
                {cosine, -sinus, 0},
                {sinus,  cosine, 0},
                {0,      0,      1}
        } *
            direction_;
    }
}

void Light::change_intensity(double factor) {
    factor = std::max(factor, 0.0);
    intensity_ *= factor;
    intensity_ = std::min(intensity_, 1.0);
}

Color Light::darken_triangle_color(const Triangle &triangle) const {
    Vector3 normal = triangle.get_normal();
    Color color = triangle.triangle_color;
    if (normal == Vector3{0, 0, 0}) {
        return darken(color, intensity_);
    }
    double cosine = std::max(std::min(-direction_.dot(normal), 1.0), 0.0);
    double factor = 0.1 + 0.9 * cosine * intensity_;
    return darken(color, factor);
}

} // namespace renderer
