#include "triangle.h"

namespace renderer {

Triangle::Triangle(Point a, Point b, Point c, Color color)
    : a_(a), b_(b), c_(c), normal_(calculate_triangle_normal(a, b, c)), triangle_color(color) {
}

void Triangle::sort_vertices_by_z() {
    if (a_.z > b_.z) {
        std::swap(a_, b_);
    }
    if (b_.z > c_.z) {
        std::swap(b_, c_);
    }
    if (a_.z > b_.z) {
        std::swap(a_, b_);
    }
}

Point Triangle::get_a() const {
    return a_;
}

Point Triangle::get_b() const {
    return b_;
}

Point Triangle::get_c() const {
    return c_;
}

Vector3 Triangle::get_normal() const {
    return normal_;
}

void Triangle::resize(double factor) {
    a_ = a_ * factor;
    b_ = b_ * factor;
    c_ = c_ * factor;
}

Triangle::Triangle(Point a, Point b, Point c, Vector3 normal, Color color)
    : a_(a), b_(b), c_(c), normal_(normal), triangle_color(color) {
}

Vector3 calculate_triangle_normal(Point a, Point b, Point c) {
    Vector3 side1 = to_Vector3(b - a);
    Vector3 side2 = to_Vector3(c - a);
    Vector3 normal = side1.cross(side2);
    normal.normalize();
    return normal;
}

ScreenTriangle::ScreenTriangle(const Triangle &triangle, Color color, double height_step, double width_step) {
    ScreenPoint a = ScreenPoint(triangle.get_a(), height_step, width_step);
    ScreenPoint b = ScreenPoint(triangle.get_b(), height_step, width_step);
    ScreenPoint c = ScreenPoint(triangle.get_c(), height_step, width_step);
    if (a.x > b.x) {
        std::swap(a, b);
    }
    if (b.x > c.x) {
        std::swap(b, c);
    }
    if (a.x > b.x) {
        std::swap(a, b);
    }
    a_ = a;
    b_ = b;
    c_ = c;
    triangle_color = color;
}

ScreenTriangle::LowerUpperY ScreenTriangle::get_lower_upper_y(int32_t x) const {
    assert(a_.x <= x && x <= c_.x && "Triangle has no points with x coordinate");
    if (a_.x == c_.x) {
        return {std::min(std::min(a_.y, b_.y), c_.y), std::max(std::max(a_.y, b_.y), c_.y)};
    }
    int32_t y1 = a_.y + (c_.y - a_.y) * (x - a_.x) / (c_.x - a_.x);
    int32_t y2;
    if (x < b_.x) {
        y2 = a_.y + (b_.y - a_.y) * (x - a_.x) / (b_.x - a_.x);
    } else {
        y2 = c_.y + (b_.y - c_.y) * (x - c_.x) / (b_.x - c_.x);
    }
    if (y1 <= y2) {
        return {y1, y2};
    }
    return {y2, y1};
}

double ScreenTriangle::get_z(int32_t x, int32_t y) const {
    assert(a_.x <= x && x <= c_.x && "Triangle has no points with x coordinate");
    int32_t double_area = (b_.x - a_.x) * (c_.y - a_.y) - (c_.x - a_.x) * (b_.y - a_.y);
    if (double_area == 0) {
        return 2;
    }
    double a_factor = static_cast<double>((b_.x - x) * (c_.y - y) - (c_.x - x) * (b_.y - y)) / double_area;
    double b_factor = -static_cast<double>((a_.x - x) * (c_.y - y) - (c_.x - x) * (a_.y - y)) / double_area;
    double c_factor = 1 - a_factor - b_factor;
    return a_.z * a_factor + b_.z * b_factor + c_.z * c_factor;
}

ScreenPoint ScreenTriangle::get_first_point_by_x() const {
    return a_;
}

ScreenPoint ScreenTriangle::get_second_point_by_x() const {
    return b_;
}

ScreenPoint ScreenTriangle::get_third_point_by_x() const {
    return c_;
}

} // namespace renderer
