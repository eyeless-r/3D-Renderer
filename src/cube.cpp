#include "cube.h"

namespace renderer {

Cube::Cube(Point shift, double side, Color color)
    : Object({
          Triangle(shift, shift + Point::Ex * side, shift + Point::Ey * side, Vector3{0, 0, -1}, color),
          Triangle(shift + Point::Ex * side + Point::Ey * side, shift + Point::Ex * side, shift + Point::Ey * side,
                   Vector3{0, 0, -1}, color),
          Triangle(shift, shift + Point::Ex * side, shift + Point::Ez * side, Vector3{0, -1, 0}, color),
          Triangle(shift + Point::Ex * side + Point::Ez * side, shift + Point::Ex * side, shift + Point::Ez * side,
                   Vector3{0, -1, 0}, color),
          Triangle(shift, shift + Point::Ey * side, shift + Point::Ez * side, Vector3{-1, 0, 0}, color),
          Triangle(shift + Point::Ey * side + Point::Ez * side, shift + Point::Ey * side, shift + Point::Ez * side,
                   Vector3{-1, 0, 0}, color),
          Triangle(shift + Point::Ez * side, shift + Point::Ez * side + Point::Ex * side,
                   shift + Point::Ez * side + Point::Ey * side, Vector3{0, 0, 1}, color),
          Triangle(shift + Point::Ez * side + Point::Ex * side + Point::Ey * side,
                   shift + Point::Ez * side + Point::Ex * side, shift + Point::Ez * side + Point::Ey * side,
                   Vector3{0, 0, 1}, color),
          Triangle(shift + Point::Ey * side, shift + Point::Ey * side + Point::Ex * side,
                   shift + Point::Ey * side + Point::Ez * side, Vector3{0, 1, 0}, color),
          Triangle(shift + Point::Ey * side + Point::Ex * side + Point::Ez * side,
                   shift + Point::Ey * side + Point::Ex * side, shift + Point::Ey * side + Point::Ez * side,
                   Vector3{0, 1, 0}, color),
          Triangle(shift + Point::Ex * side, shift + Point::Ex * side + Point::Ey * side,
                   shift + Point::Ex * side + Point::Ez * side, Vector3{1, 0, 0}, color),
          Triangle(shift + Point::Ex * side + Point::Ey * side + Point::Ez * side,
                   shift + Point::Ex * side + Point::Ey * side, shift + Point::Ex * side + Point::Ez * side,
                   Vector3{1, 0, 0}, color),
      }) {
}

} // namespace renderer