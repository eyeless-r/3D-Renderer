#include "application.h"

namespace renderer {

Application::Application()
    : renderer_(Height{kScreenHeight}, Width{kScreenWidth}), world_(),
      camera_(kCameraHeight, kCameraWidth, kCameraFrontDistance, kCameraBackDistance, kCameraFocus),
      light_(kLightIntensity, kLightDirection), window_(sf::VideoMode({kScreenHeight, kScreenWidth}), "3D Renderer") {
}

void Application::add_object(ObjectPtr &&object_ptr) {
    world_.objects.push_back(std::move(object_ptr));
}

void Application::run() {
    while (window_.isOpen()) {
        window_.clear();
        handle_events();
        handle_keyboard();
        std::vector<sf::Vertex> pixels = renderer_.render(world_, camera_, light_).get_pixels();
        window_.draw(pixels.data(), pixels.size(), sf::PrimitiveType::Points);
        window_.display();
    }
}

void Application::handle_events() {
    while (const std::optional event = window_.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window_.close();
            return;
        }
    }
}

void Application::move_camera() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) {
        camera_.move_camera(Axis::Z, 1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
        camera_.move_camera(Axis::Z, -1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        camera_.move_camera(Axis::X, 1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        camera_.move_camera(Axis::X, -1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        camera_.move_camera(Axis::Y, 1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        camera_.move_camera(Axis::Y, -1);
    }
}

void Application::rotate_camera() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
        camera_.rotate_camera(Axis::Z, 0.02);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
        camera_.rotate_camera(Axis::Z, -0.02);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        camera_.rotate_camera(Axis::Y, 0.02);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        camera_.rotate_camera(Axis::Y, -0.02);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        camera_.rotate_camera(Axis::X, 0.02);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        camera_.rotate_camera(Axis::X, -0.02);
    }
}

void Application::rotate_light() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) {
        light_.rotate_light(Axis::Y, 0.02);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) {
        light_.rotate_light(Axis::Y, -0.02);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) {
        light_.rotate_light(Axis::X, 0.02);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) {
        light_.rotate_light(Axis::X, -0.02);
    }
}

void Application::change_light_intensity() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y)) {
        light_.change_intensity(1.0 / 0.9);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) {
        light_.change_intensity(0.9);
    }
}

void Application::handle_keyboard() {
    move_camera();
    rotate_camera();
    rotate_light();
    change_light_intensity();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        window_.close();
        return;
    }
}

const Point Application::kCameraFocus = Point{0, 0, -20};
const Vector3 Application::kLightDirection = Vector3{0, 0, 1};

} // namespace renderer