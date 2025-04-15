#include <SFML/Window/Keyboard.hpp>

#include "screen.h"

namespace renderer {

class View {
public:
    View(sf::RenderWindow *window);
    void show(const Screen &screen);

private:
    sf::RenderWindow *window_;
};

} // namespace renderer
