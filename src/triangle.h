#pragma once

#include "color.h"
#include "linalg.h"
#include "point.h"

namespace renderer {

static const Color default_triangle_color = Color::White;

class Triangle {
public:
    Triangle(Point a, Point b, Point c, Color color = default_triangle_color);
    void sort_vertices_by_z();
    Point get_a() const;
    Point get_b() const;
    Point get_c() const;
    Vector3 get_normal() const;
    void resize(double factor);

    friend class Parser;
    friend class Cube;
    friend class Tetraedr;

    Color triangle_color;

protected:
    Triangle(Point a, Point b, Point c, Vector3 normal, Color color = default_triangle_color);

    Point a_;
    Point b_;
    Point c_;
    Vector3 normal_;
};

Vector3 calculate_triangle_normal(Point a, Point b, Point c);

class ScreenTriangle {
public:
    struct LowerUpperY {
        int32_t lower_y;
        int32_t upper_y;
    };

    ScreenTriangle(const Triangle &triangle, Color color, double height_step, double width_step);
    LowerUpperY get_lower_upper_y(int32_t x) const;
    double get_z(int32_t x, int32_t y) const;
    ScreenPoint get_first_point_by_x() const;
    ScreenPoint get_second_point_by_x() const;
    ScreenPoint get_third_point_by_x() const;

    Color triangle_color = default_triangle_color;

private:
    ScreenPoint a_;
    ScreenPoint b_;
    ScreenPoint c_;
};

} // namespace renderer
