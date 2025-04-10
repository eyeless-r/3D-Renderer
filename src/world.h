#include "cube.h"
#include "object.h"
#include "tetraedr.h"

namespace renderer {

using ObjectPtr = std::unique_ptr<Object>;

struct World {
    std::vector<ObjectPtr> objects = std::vector<ObjectPtr>();
};

} // namespace renderer