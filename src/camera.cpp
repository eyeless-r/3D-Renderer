#include "camera.h"

namespace renderer {

Camera::Camera(double height, double width, double front_plane_distance, double back_plane_distance, Point focus)
    : height_(height), width_(width), back_plane_distance_(back_plane_distance),
      front_plane_distance_(front_plane_distance), focus_(focus),
      focus_to_infinity_(get_focus_to_infinity_matrix(height, width, front_plane_distance, back_plane_distance)) {
}

void Camera::move_camera(Axis axis, double shift) {
    Vector3 shift_vector;
    switch (axis) {
    case Axis::X:
        shift_vector = shift * camera_basis_rotation_.col(0);
        break;
    case Axis::Y:
        shift_vector = shift * camera_basis_rotation_.col(1);
        break;
    default:
        shift_vector = shift * camera_basis_rotation_.col(2);
    }
    focus_.x += shift_vector[0];
    focus_.y += shift_vector[1];
    focus_.z += shift_vector[2];
}

void Camera::rotate_camera(Axis axis, double angle) {
    double cosine = cos(angle);
    double sinus = sin(angle);
    switch (axis) {
    case Axis::X:
        camera_basis_rotation_ *= Matrix3{
            {1, 0,      0     },
            {0, cosine, -sinus},
            {0, sinus,  cosine},
        };
        return;
    case Axis::Y:
        camera_basis_rotation_ *= Matrix3{
            {cosine, 0, sinus },
            {0,      1, 0     },
            {-sinus, 0, cosine}
        };
        return;
    default:
        camera_basis_rotation_ *= Matrix3{
            {cosine, -sinus, 0},
            {sinus,  cosine, 0},
            {0,      0,      1}
        };
    }
}

double Camera::get_height() const {
    return height_;
}

double Camera::get_width() const {
    return width_;
}

std::vector<Triangle> Camera::clip_transform_triangle(Triangle triangle) const {
    triangle = triangle_in_camera_coordinates(triangle);
    triangle.sort_vertices_by_z();
    if (triangle.get_a().z >= front_plane_distance_) {
        return {transform_triangle_coordinates(triangle)};
    }
    if (triangle.get_c().z <= front_plane_distance_) {
        return {};
    }
    Point ac_intersection = find_segment_intersection_with_front_plane(triangle.get_a(), triangle.get_c());
    if (triangle.get_b().z <= front_plane_distance_) {
        Point bc_intersection = find_segment_intersection_with_front_plane(triangle.get_b(), triangle.get_c());
        return {transform_triangle_coordinates(
            Triangle(triangle.get_c(), ac_intersection, bc_intersection, triangle.triangle_color))};
    }
    Point ab_intersection = find_segment_intersection_with_front_plane(triangle.get_a(), triangle.get_b());
    return {transform_triangle_coordinates(
                Triangle(triangle.get_c(), ac_intersection, ab_intersection, triangle.triangle_color)),
            transform_triangle_coordinates(
                Triangle(triangle.get_c(), ab_intersection, triangle.get_b(), triangle.triangle_color))};
}

Point Camera::point_in_camera_coordinates(const Point p) const {
    Vector3 coordinates = {p.x - focus_.x, p.y - focus_.y, p.z - focus_.z};
    Vector3 new_coordinates = camera_basis_rotation_.transpose() * coordinates;
    return Point{new_coordinates[0], new_coordinates[1], new_coordinates[2]};
}

Triangle Camera::triangle_in_camera_coordinates(const Triangle &triangle) const {
    return Triangle(point_in_camera_coordinates(triangle.get_a()), point_in_camera_coordinates(triangle.get_b()),
                    point_in_camera_coordinates(triangle.get_c()), triangle.triangle_color);
}

Point Camera::transform_point_coordinates(const Point p) const {
    Vector4 coordinates = {p.x, p.y, p.z, 1.0};
    Vector4 new_coordinates = focus_to_infinity_ * coordinates;
    assert(new_coordinates[3] > kEps || new_coordinates[3] < -kEps);
    new_coordinates /= new_coordinates[3];
    return Point{new_coordinates[0], new_coordinates[1], new_coordinates[2]};
}

Triangle Camera::transform_triangle_coordinates(const Triangle &triangle) const {
    return Triangle(transform_point_coordinates(triangle.get_a()), transform_point_coordinates(triangle.get_b()),
                    transform_point_coordinates(triangle.get_c()), triangle.triangle_color);
}

Point Camera::find_segment_intersection_with_front_plane(Point a, Point b) const {
    if (a.z > b.z) {
        std::swap(a, b);
    }
    assert(a.z <= front_plane_distance_ && b.z > front_plane_distance_ &&
           "The segment does not intersect the front plane");
    double factor = (b.z - front_plane_distance_) / (b.z - a.z);
    return b * (1 - factor) + a * factor;
}

Matrix4 get_focus_to_infinity_matrix(double height, double width, double front_plane_distance,
                                     double back_plane_distance) {
    assert(height > 0 && width > 0 && "Camera height and width should be positive");
    assert(front_plane_distance < back_plane_distance);
    double z_factor = back_plane_distance / (back_plane_distance - front_plane_distance);
    double t_factor = -front_plane_distance * z_factor;
    return Matrix4{
        {front_plane_distance, 0,                    width / 2,  0       },
        {0,                    front_plane_distance, height / 2, 0       },
        {0,                    0,                    z_factor,   t_factor},
        {0,                    0,                    1,          0       },
    };
}

} // namespace renderer
