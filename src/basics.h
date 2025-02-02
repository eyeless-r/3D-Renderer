#pragma once

#include <Eigen/Core>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace renderer {

const double EPS = 0.00001;

using Color = sf::Color;
using PointVector = Eigen::Vector4d;
using TransformMatrix = Eigen::Matrix4d;
using Window = sf::RenderWindow;

}  // namespace renderer
