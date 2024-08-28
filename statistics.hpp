#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include "boids.hpp"

namespace pf {

float mean_position(std::vector<Boid> const& flock);

float standdev_position(std::vector<Boid> const& flock);

float mean_velocity(std::vector<Boid> const& flock);

float standdev_velocity(std::vector<Boid> const& flock);

float mean_distance(std::vector<Boid> const& flock);

float standdev_distance(std::vector<Boid> const& flock);

} // namespace pf

#endif