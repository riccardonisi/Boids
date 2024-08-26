#include "statistics.hpp"

namespace pf {
float mean_velocity(std::vector<Boid> const& stormo)
{
  float sum{0};
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    sum += distanza(stormo[i].get_vel(), {0, 0});
  }
  return sum / static_cast<float>((stormo.size()));
}

float mean_position(std::vector<Boid> const& stormo)
{
  float sum{0};
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    sum += distanza(stormo[i].get_pos(), {0, 0});
  }
  return sum / static_cast<float>((stormo.size()));
}

float standdev_velocity(std::vector<Boid> const& stormo)
{
  float sum{0};
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    sum += powf((distanza(stormo[i].get_vel(), {0, 0}) - mean_velocity(stormo)),
                2);
  }
  return std::sqrt(sum / static_cast<float>((stormo.size() - 1)));
}

float standdev_position(std::vector<Boid> const& stormo)
{
  float sum{0};
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    sum += powf((distanza(stormo[i].get_pos(), {0, 0}) - mean_position(stormo)),
                2);
  }
  return std::sqrt(sum / static_cast<float>((stormo.size() - 1)));
}

float mean_distance(std::vector<Boid> const& stormo)
{
  float sum{0};
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    for (unsigned long int j{0}; j != i; ++j) {
      sum += distanza(stormo[i].get_pos(), stormo[j].get_pos());
    }
  }
  return 2.0f * sum
       / (static_cast<float>(stormo.size())
          * (static_cast<float>(stormo.size()) - 1));
}

float standdev_distance(std::vector<Boid> const& stormo)
{
  float sum{0};
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    for (unsigned long int j{0}; j != i; ++j) {
      sum += powf((distanza(stormo[i].get_pos(), stormo[j].get_pos())
                   - mean_distance(stormo)),
                  2);
    }
  }
  return std::sqrt(sum
                   / ((static_cast<float>(stormo.size())
                       * (static_cast<float>(stormo.size()) - 1))
                          / 2.0f
                      - 1.0f));
}
} // namespace pf