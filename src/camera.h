#include "basics.h"
#include "triangle.h"

namespace renderer {
class Camera {
public:
    Camera(double height, double width, double front_plane_distance, double back_plane_distance, Point focus);

    Point transform_point_coordinates(const Point& p) const;

    Triangle transform_triangle_coordinates(const Triangle& triangle) const;

    void move_camera(const double x_shift, const double y_shift, const double z_shift);

    void rotate_camera(double x_axis_angle, double y_axis_angle, double z_axis_angle);

    double get_height() const;

    double get_width() const;

private:
    void update_focus_to_infinity_matrix();

    double height_;
    double width_;
    double front_plane_distance_;
    double back_plane_distance_;
    Point focus_ = Point();
    TransformMatrix reverse_rotation_ = TransformMatrix::Identity();
    TransformMatrix focus_to_infinity_ = TransformMatrix::Identity();
};
}  // namespace renderer
