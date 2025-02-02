#include "src/renderer.h"

using Point = renderer::Point;

int main() {
    renderer::Window window(sf::VideoMode({800, 800}), "3D Renderer");
    renderer::Renderer render(800, 800);
    renderer::Camera camera(20, 20, 7, 40, Point(0, 0, -7));
    camera.rotate_camera(0, 0.3, -0.1);

    renderer::Triangle triangle1(Point(10, 0, 15), Point(5, 10, 10), Point(-5, -5, 10),
                                 renderer::Color::Blue);  // some tests
    render.add_triangle(triangle1, camera);
    renderer::Triangle triangle2(Point(-15, 10, 20), Point(15, -5, 5), Point(10, -10, 5), renderer::Color::Red);
    render.add_triangle(triangle2, camera);
    renderer::Triangle triangle3(Point(15, -2, 10), Point(-10, -5, 12), Point(-3, -15, 10), renderer::Color::Green);
    render.add_triangle(triangle3, camera);

    while (window.isOpen()) {
        window.clear();
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        render.display(window);
        window.display();
    }
}
