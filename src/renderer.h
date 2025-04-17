#include "camera.h"
#include "light.h"
#include "screen.h"
#include "triangle.h"
#include "world.h"

namespace renderer {

class Renderer {
public:
    Renderer(Height height, Width width);
    void draw_triangle(const Triangle &triangle, Screen &screen, const Camera &camera, const Light &light) const;
    Screen render(const World &world, const Camera &camera, const Light &light) const;

private:
    void draw_screen_triangle(const ScreenTriangle &triangle, Screen &screen) const;

    Height height_;
    Width width_;
};

} // namespace renderer
