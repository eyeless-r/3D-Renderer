#include "renderer.h"
#include <SFML/Window/Keyboard.hpp>

namespace renderer {

class Application {
public:
    using Window = sf::RenderWindow;

    Application();
    void add_object(ObjectPtr &&object_ptr);
    void run();

private:
    void handle_events();
    void move_camera();
    void rotate_camera();
    void rotate_light();
    void change_light_intensity();
    void handle_keyboard();

    static constexpr uint32_t kScreenHeight = 1000;
    static constexpr uint32_t kScreenWidth = 1000;
    static constexpr double kCameraHeight = 20;
    static constexpr double kCameraWidth = 20;
    static constexpr double kCameraFrontDistance = 5;
    static constexpr double kCameraBackDistance = 100;
    static constexpr double kLightIntensity = 1;
    static const Point kCameraFocus;
    static const Vector3 kLightDirection;

    Renderer renderer_;
    Camera camera_;
    Light light_;
    World world_;
    Window window_;
};

} // namespace renderer
