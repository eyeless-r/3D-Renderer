#include "object.h"

namespace renderer {

class Cube : public Object {
public:
    Cube(Point shift, double side, Color color);
};

} // namespace renderer
