#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include "boids.hpp"
#include <cmath>
#include <iostream>
#include <vector>

namespace pf {

double mean_velocity(std::vector<Boid> const& stormo);

double mean_position(std::vector<Boid> const& stormo);

double standdev_velocity(std::vector<Boid> const& stormo);

double standdev_position(std::vector<Boid> const& stormo);

double mean_distance(std::vector<Boid> const& stormo);

double standdev_distance(std::vector<Boid> const& stormo);

} // namespace pf

#endif