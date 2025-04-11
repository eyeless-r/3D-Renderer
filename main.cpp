#include "src/application.h"
#include "src/except.h"
#include "src/parser.h"

int main() {
    using namespace renderer;
    try {
        Application app;

        Object snail = Parser::parse("../models/snail.obj", Color::White);
        snail.resize(2);
        app.add_object(std::make_unique<Object>(snail));

        Point a1{5, 0, 40};
        Point b1{5, 10, 60};
        Point c1{-5, -5, 35};
        Point d1{2, 2, 25};
        Tetraedr tetraedr1 = Tetraedr(a1, b1, c1, d1, Color::Blue, Color::Green, Color::Red, Color::Yellow);
        app.add_object(std::make_unique<Object>(tetraedr1));

        Point a2{10, 5, 20};
        Point b2{5, 5, 50};
        Point c2{-5, 10, 40};
        Point d2{0, 0, 45};
        Tetraedr tetraedr2 = Tetraedr(a2, b2, c2, d2, Color::Blue, Color::Green, Color::Red, Color::Yellow);
        app.add_object(std::make_unique<Object>(tetraedr2));

        Point shift{15, 0, 10};
        Cube cube = Cube(shift, 5, Color::Yellow);
        app.add_object(std::make_unique<Object>(cube));

        app.run();
    } catch (...) {
        except::react();
    }
    return 0;
}
