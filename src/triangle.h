#pragma once

#include "basics.h"
#include "point.h"

namespace renderer {

struct Triangle {
    Triangle(Point a, Point b, Point c, Color color = Color::Black);

    void sort_vertices();

    std::pair<double, double> get_lower_upper_y(double x);

    double get_z(double x, double y);

    Point a, b, c;  // to do: add normals
    Color color;
};
}  // namespace renderer
