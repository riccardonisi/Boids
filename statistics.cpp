#include "statistics.hpp"

namespace pf {
double mean_velocity(std::vector<Boid> const& stormo)
{
  double sum{0};
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    sum += distanza(stormo[i].get_vel(), {0, 0});
  }
  return sum / static_cast<double>(stormo.size());
}

double mean_position(std::vector<Boid> const& stormo)
{
  double sum{0};
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    sum += distanza(stormo[i].get_pos(), {0, 0});
  }
  return sum / static_cast<double>(stormo.size());
}

double standdev_velocity(std::vector<Boid> const& stormo)
{
  double sum{0};
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    sum +=
        pow((distanza(stormo[i].get_vel(), {0, 0}) - mean_velocity(stormo)), 2);
  }
  return std::sqrt(sum / static_cast<double>(stormo.size() - 1));
}

double standdev_position(std::vector<Boid> const& stormo)
{
  double sum{0};
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    sum +=
        pow((distanza(stormo[i].get_pos(), {0, 0}) - mean_position(stormo)), 2);
  }
  return std::sqrt(sum / static_cast<double>(stormo.size() - 1));
}

double mean_distance(std::vector<Boid> const& stormo)
{
  double sum{0};
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    for (unsigned long int j{0}; j != i; ++j) {
      sum += distanza(stormo[i].get_pos(), stormo[j].get_pos());
    }
  }
  return 2.0 * sum
       / (static_cast<double>(stormo.size())
          * (static_cast<double>(stormo.size()) - 1));
}

double standdev_distance(std::vector<Boid> const& stormo)
{
  double sum{0};
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    for (unsigned long int j{0}; j != i; ++j) {
      sum += pow((distanza(stormo[i].get_pos(), stormo[j].get_pos())
                  - mean_distance(stormo)),
                 2);
    }
  }
  return std::sqrt(sum
                   / ((static_cast<double>(stormo.size())
                       * (static_cast<double>(stormo.size()) - 1))
                          / 2.0
                      - 1.0));
}
} // namespace pf