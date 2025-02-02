#include "camera.h"
#include "screen.h"
#include "triangle.h"

namespace renderer {
class Renderer {
public:
    Renderer(size_t height, size_t width);

    // to do: add clipping

    void add_triangle(const Triangle& triangle, const Camera& camera);

    void display(Window& window);

private:
    Screen screen_;
};
}  // namespace renderer
