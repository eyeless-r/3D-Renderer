#include "object.h"
#include <vector>

namespace renderer {

Object::Object(std::vector<Triangle> triangles) : triangles_(triangles) {
}

void Object::resize(double factor) {
    for (Triangle &triangle : triangles_) {
        triangle.resize(factor);
    }
}

std::vector<Triangle> Object::get_triangles() const {
    return triangles_;
}

} // namespace renderer