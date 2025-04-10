#pragma once
#include "linalg.h"

namespace renderer {

struct Point {
    static const Point Ex;
    static const Point Ey;
    static const Point Ez;

    double x = 0;
    double y = 0;
    double z = 0;
};

Vector3 to_Vector3(Point p);

Point operator+(Point a, Point b);
Point operator-(Point a, Point b);
Point operator*(Point a, double factor);

struct ScreenPoint {
    ScreenPoint() = default;
    ScreenPoint(Point p, double height_step, double width_step);

    int32_t x = 0;
    int32_t y = 0;
    double z = 0;
};

} // namespace renderer
