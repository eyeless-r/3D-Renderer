#include "triangle.h"

namespace renderer {

Triangle::Triangle(Point a, Point b, Point c, Color color) : a(a), b(b), c(c), color_(color){};

Color Triangle::get_color() const {
    return color_;
}

void Triangle::sort_vertices() {
    if (a.x > b.x) {
        std::swap(a, b);
    }
    if (b.x > c.x) {
        std::swap(b, c);
    }
    if (a.x > b.x) {
        std::swap(a, b);
    }
}

std::pair<double, double> Triangle::get_lower_upper_y(double x) {
    sort_vertices();
    assert(a.x - EPS <= x && x <= c.x + EPS && "Triangle has no points with x coordinate");
    if (x < a.x) {
        x = a.x;
    } else if (x > c.x) {
        x = c.x;
    }
    double y1 = a.y + (c.y - a.y) * (x - a.x) / (c.x - a.x);  // to do: what if c.x == a.x ? triangle -> line
    double y2;
    if (x < b.x) {
        y2 = a.y + (b.y - a.y) * (x - a.x) / (b.x - a.x);
    } else {
        y2 = c.y + (b.y - c.y) * (x - c.x) / (b.x - c.x);
    }
    if (y1 < y2) {
        return {y1, y2};
    }
    return {y2, y1};
}

double Triangle::get_z(double x, double y) {
    sort_vertices();
    assert(a.x - EPS <= x && x <= c.x + EPS && "Triangle has no points with this x coordinate");
    if (x < a.x) {
        x = a.x;
    } else if (x > c.x) {
        x = c.x;
    }
    double y1 = a.y + (c.y - a.y) * (x - a.x) / (c.x - a.x);  // to do: c.x == a.x
    double z1 = a.z + (c.z - a.z) * (x - a.x) / (c.x - a.x);
    double y2;
    double z2;
    if (x < b.x) {
        y2 = a.y + (b.y - a.y) * (x - a.x) / (b.x - a.x);
        z2 = a.z + (b.z - a.z) * (x - a.x) / (b.x - a.x);
    } else {
        y2 = c.y + (b.y - c.y) * (x - c.x) / (b.x - c.x);
        z2 = c.z + (b.z - c.z) * (x - c.x) / (b.x - c.x);
    }
    if (y1 > y2) {
        std::swap(y1, y2);
    }
    assert(y1 - EPS <= y && y <= y2 + EPS && "Triangle has no points with these (x, y) coordinates");
    if (y1 == y2) {
        return z1;
    }
    if (y < y1) {
        y = y1;
    } else if (y > y2) {
        y = y2;
    }
    return z1 + (z2 - z1) * (y - y1) / (y2 - y1);
}
}  // namespace renderer
