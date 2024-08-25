#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include "boids.hpp"

namespace pf {

float mean_velocity(std::vector<Boid> const& stormo);

float mean_position(std::vector<Boid> const& stormo);

float standdev_velocity(std::vector<Boid> const& stormo);

float standdev_position(std::vector<Boid> const& stormo);

float mean_distance(std::vector<Boid> const& stormo);

float standdev_distance(std::vector<Boid> const& stormo);

} // namespace pf

#endif