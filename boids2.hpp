#include "boids.hpp"
#include <iostream>
#include <vector>
#include <cmath>

namespace pf {
double mean_velocity(std::vector<Boid> stormo)
{
  double sum{0};
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    sum += distanza(stormo[i].vel(), {0, 0});
  }
  return sum / static_cast<double>(stormo.size());
}
double mean_position(std::vector<Boid> stormo)
{
  double sum{0};
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    sum += distanza(stormo[i].pos(), {0, 0});
  }
  return sum / static_cast<double>(stormo.size());
}
double standdev_velocity(std::vector<Boid> stormo)
{
  double sum{0};
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    sum += pow((distanza(stormo[i].vel(), {0, 0}) - mean_velocity(stormo)), 2);
  }
  return std::sqrt(sum / static_cast<double>(stormo.size() - 1));
}
double standdev_position(std::vector<Boid> stormo)
{
  double sum{0};
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    sum += pow((distanza(stormo[i].pos(), {0, 0}) - mean_position(stormo)), 2);
  }
  return std::sqrt(sum / static_cast<double>(stormo.size() - 1));
}
} // namespace pf