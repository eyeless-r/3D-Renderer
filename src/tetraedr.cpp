#include "tetraedr.h"

namespace renderer {

Tetraedr::Tetraedr(Point a, Point b, Point c, Point d, Color color_abc, Color color_abd, Color color_acd,
                   Color color_bcd)
    : Object({
          Triangle{a, b, c, calculate_tetraedr_triangle_normal(a, b, c, d), color_abc},
          Triangle(a, b, d, calculate_tetraedr_triangle_normal(a, b, d, c), color_abd),
          Triangle(a, c, d, calculate_tetraedr_triangle_normal(a, c, d, b), color_acd),
          Triangle(b, c, d, calculate_tetraedr_triangle_normal(b, c, d, a), color_bcd)
}) {
}

Vector3 calculate_tetraedr_triangle_normal(Point a, Point b, Point c, Point d) {
    Vector3 side1 = to_Vector3(b - a);
    Vector3 side2 = to_Vector3(c - a);
    Vector3 abc_normal = side1.cross(side2);
    abc_normal.normalize();
    if (abc_normal.dot(to_Vector3(d - a)) < 0) {
        return abc_normal;
    }
    return -abc_normal;
}

} // namespace renderer