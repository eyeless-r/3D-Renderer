#include "view.h"

namespace app {

View::View(sf::RenderWindow *window) : window_(window) {
}

void View::show(const Screen &screen) {
    window_->clear();
    std::vector<sf::Vertex> pixels = screen.get_pixels();
    window_->draw(pixels.data(), pixels.size(), sf::PrimitiveType::Points);
    window_->display();
}

} // namespace app
