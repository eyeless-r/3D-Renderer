#include "point.h"

namespace renderer {

const Point Point::Ex{1, 0, 0};
const Point Point::Ey{0, 1, 0};
const Point Point::Ez{0, 0, 1};

Vector3 to_Vector3(Point p) {
    return Vector3{p.x, p.y, p.z};
}

Point operator+(Point a, Point b) {
    return Point{a.x + b.x, a.y + b.y, a.z + b.z};
}

Point operator-(Point a, Point b) {
    return Point{a.x - b.x, a.y - b.y, a.z - b.z};
}

Point operator*(Point a, double factor) {
    return Point{factor * a.x, factor * a.y, factor * a.z};
}

ScreenPoint::ScreenPoint(Point p, double height_step, double width_step) {
    assert(height_step > 0 && "Can not pixelize with non positive height step");
    assert(width_step > 0 && "Can not pixelize with non positive width step");
    x = round(p.x * width_step - 0.5);
    y = round(p.y * height_step - 0.5);
    z = p.z;
}

} // namespace renderer
