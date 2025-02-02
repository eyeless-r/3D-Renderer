#include "camera.h"

namespace renderer {
Camera::Camera(double height, double width, double front_plane_distance, double back_plane_distance, Point focus)
    : height_(height),
      width_(width),
      back_plane_distance_(back_plane_distance),
      front_plane_distance_(front_plane_distance),
      focus_(focus),
      reverse_rotation_(TransformMatrix::Identity()) {
    assert(front_plane_distance_ < back_plane_distance);
    update_focus_to_infinity_matrix();
}

Point Camera::transform_point_coordinates(const Point& p) const {
    PointVector coordinates = {p.x - focus_.x, p.y - focus_.y, p.z - focus_.z, 1.0};
    PointVector new_coordinates = focus_to_infinity_ * reverse_rotation_ * coordinates;
    assert(new_coordinates[3] > EPS || new_coordinates[3] < -EPS);
    new_coordinates /= new_coordinates[3];
    return Point(new_coordinates[0], new_coordinates[1], new_coordinates[2]);
}

Triangle Camera::transform_triangle_coordinates(const renderer::Triangle& triangle) const {
    return Triangle(transform_point_coordinates(triangle.a), transform_point_coordinates(triangle.b),
                    transform_point_coordinates(triangle.c), triangle.color);
}

void Camera::move_camera(const double x_shift, const double y_shift, const double z_shift) {
    focus_.x += x_shift;
    focus_.y += y_shift;
    focus_.z += z_shift;
}

void Camera::rotate_camera(double x_axis_angle, double y_axis_angle, double z_axis_angle) {  // maybe something wrong
    double cosine = cos(x_axis_angle);
    double sinus = sin(x_axis_angle);
    TransformMatrix x_axis_rotation{
        {1, 0,      0,      0},
        {0, cosine, sinus,  0},
        {0, -sinus, cosine, 0},
        {0, 0,      0,      1}
    };
    cosine = cos(y_axis_angle);
    sinus = sin(y_axis_angle);
    TransformMatrix y_axis_rotation{
        {cosine, 0, -sinus, 0},
        {0,      1, 0,      0},
        {sinus,  0, cosine, 0},
        {0,      0, 0,      1}
    };
    cosine = cos(z_axis_angle);
    sinus = sin(z_axis_angle);
    TransformMatrix z_axis_rotation{
        {cosine, sinus,  0, 0},
        {-sinus, cosine, 0, 0},
        {0,      0,      1, 0},
        {0,      0,      0, 1}
    };
    reverse_rotation_ *= x_axis_rotation * y_axis_rotation * z_axis_rotation;
}

double Camera::get_height() const {
    return height_;
}

double Camera::get_width() const {
    return width_;
}

void Camera::update_focus_to_infinity_matrix() {
    double z_coefficient = back_plane_distance_ / (back_plane_distance_ - front_plane_distance_);
    double t_coefficient = -front_plane_distance_ * z_coefficient;
    focus_to_infinity_ = TransformMatrix{
        {front_plane_distance_, 0,                     width_ / 2,    0            },
        {0,                     front_plane_distance_, height_ / 2,   0            },
        {0,                     0,                     z_coefficient, t_coefficient},
        {0,                     0,                     1,             0            },
    };
}
}  // namespace renderer
