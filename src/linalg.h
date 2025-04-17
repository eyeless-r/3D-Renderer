#pragma once

#include <Eigen/Core>
#include <Eigen/Geometry>

namespace renderer {

constexpr double kEps = 0.00001;

using Vector3 = Eigen::Vector3d;
using Vector4 = Eigen::Vector4d;
using Matrix3 = Eigen::Matrix3d;
using Matrix4 = Eigen::Matrix4d;

} // namespace renderer
