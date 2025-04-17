#include <SFML/Window/Keyboard.hpp>

#include "../src/screen.h"

namespace app {

using namespace renderer;

class View {
public:
    View(sf::RenderWindow *window);
    void show(const Screen &screen);

private:
    sf::RenderWindow *window_;
};

} // namespace app
