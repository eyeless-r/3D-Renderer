#include "object.h"

namespace renderer {

class Tetraedr : public Object {
public:
    Tetraedr(Point a, Point b, Point c, Point d, Color color_abc, Color color_abd, Color color_acd, Color color_bcd);
};

Vector3 calculate_tetraedr_triangle_normal(Point a, Point b, Point c, Point d);

} // namespace renderer
