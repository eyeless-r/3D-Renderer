#include "renderer.h"
#include "runtime.h"
#include "view.h"

namespace renderer {

class Application {
public:
    using Window = sf::RenderWindow;

    Application();
    Application(const Application &) = delete;
    Application &operator=(const Application &) = delete;
    Application(Application &&) = delete;
    Application &operator=(const Application &&) = delete;
    void add_object(ObjectPtr &&object_ptr);
    void run();

private:
    static constexpr double kCameraHeight = 20;
    static constexpr double kCameraWidth = 20;
    static constexpr double kCameraFrontDistance = 5;
    static constexpr double kCameraBackDistance = 100;
    static constexpr double kLightIntensity = 1;
    static const Point kCameraFocus;
    static const Vector3 kLightDirection;

    Renderer renderer_;
    World world_;
    Camera camera_;
    Light light_;
    RunTime runtime_;
    View view_;
};

} // namespace renderer
