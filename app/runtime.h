#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../src/camera.h"
#include "../src/light.h"

namespace app {

using namespace renderer;

class RunTime {
public:
    RunTime();
    void run(Camera &camera, Light &light);
    sf::RenderWindow *window();
    bool is_running() const;

    static constexpr uint32_t kScreenHeight = 1000;
    static constexpr uint32_t kScreenWidth = 1000;

private:
    void move_camera(Camera &camera);
    void rotate_camera(Camera &camera);
    void rotate_light(Light &light);
    void change_light_intensity(Light &light);
    void handle_keyboard(Camera &camera, Light &light);

    sf::RenderWindow window_;
};

} // namespace app
