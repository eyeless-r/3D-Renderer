#pragma once

#include <vector>

#include "triangle.h"

namespace renderer {

class Object {
public:
    Object(std::vector<Triangle> triangles);
    void resize(double factor);
    std::vector<Triangle> get_triangles() const;

private:
    std::vector<Triangle> triangles_ = {};
};

} // namespace renderer
