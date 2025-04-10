#include "axis.h"
#include "triangle.h"

namespace renderer {

class Light {
public:
    Light(double intensity, Vector3 direction);
    void rotate_light(Axis axis, double angle);
    void change_intensity(double factor);

    Color darken_triangle_color(const Triangle &triangle) const;

private:
    double intensity_;
    Vector3 direction_;
};

} // namespace renderer
