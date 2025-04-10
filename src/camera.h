#include "axis.h"
#include "linalg.h"
#include "triangle.h"

namespace renderer {

class Camera {
public:
    Camera(double height, double width, double front_plane_distance, double back_plane_distance, Point focus);
    void move_camera(Axis axis, double shift);
    void rotate_camera(Axis axis, double angle);
    double get_height() const;
    double get_width() const;
    std::vector<Triangle> clip_transform_triangle(Triangle triangle) const;

private:
    Point point_in_camera_coordinates(const Point p) const;
    Triangle triangle_in_camera_coordinates(const Triangle &triangle) const;
    Point transform_point_coordinates(const Point p) const;
    Triangle transform_triangle_coordinates(const Triangle &triangle) const;
    Point find_segment_intersection_with_front_plane(const Point a, const Point b) const;

    double height_;
    double width_;
    double front_plane_distance_;
    double back_plane_distance_;
    Point focus_ = Point{0, 0, 0};
    Matrix3 camera_basis_rotation_ = Matrix3::Identity();
    Matrix4 focus_to_infinity_;
};

Matrix4 get_focus_to_infinity_matrix(double height, double width, double front_plane_distance,
                                     double back_plane_distance);

} // namespace renderer
