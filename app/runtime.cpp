#include "runtime.h"

namespace app {

RunTime::RunTime() : window_(sf::VideoMode({kScreenHeight, kScreenWidth}), "3D Renderer") {
}

void RunTime::run(Camera &camera, Light &light) {
    while (const std::optional event = window_.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window_.close();
            return;
        }
    }
    handle_keyboard(camera, light);
}

sf::RenderWindow *RunTime::window() {
    return &window_;
}

bool RunTime::is_running() const {
    return window_.isOpen();
}

void RunTime::move_camera(Camera &camera) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) {
        camera.move_camera(Axis::Z, 1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
        camera.move_camera(Axis::Z, -1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        camera.move_camera(Axis::X, 1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        camera.move_camera(Axis::X, -1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        camera.move_camera(Axis::Y, 1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        camera.move_camera(Axis::Y, -1);
    }
}

void RunTime::rotate_camera(Camera &camera) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
        camera.rotate_camera(Axis::Z, 0.02);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
        camera.rotate_camera(Axis::Z, -0.02);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        camera.rotate_camera(Axis::Y, 0.02);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        camera.rotate_camera(Axis::Y, -0.02);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        camera.rotate_camera(Axis::X, 0.02);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        camera.rotate_camera(Axis::X, -0.02);
    }
}

void RunTime::rotate_light(Light &light) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) {
        light.rotate_light(Axis::Y, 0.02);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) {
        light.rotate_light(Axis::Y, -0.02);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) {
        light.rotate_light(Axis::X, 0.02);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) {
        light.rotate_light(Axis::X, -0.02);
    }
}

void RunTime::change_light_intensity(Light &light) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y)) {
        light.change_intensity(1.0 / 0.9);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) {
        light.change_intensity(0.9);
    }
}

void RunTime::handle_keyboard(Camera &camera, Light &light) {
    move_camera(camera);
    rotate_camera(camera);
    rotate_light(light);
    change_light_intensity(light);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        window_.close();
        return;
    }
}

} // namespace app
