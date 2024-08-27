#include "statistics.hpp"

namespace pf {

float mean_position(std::vector<Boid> const& stormo)
{
  if (stormo.size() < 3) {
    throw std::runtime_error{
        "Non ci sono abbastanza uccelli per calcolare i parametri medi"};
  }
  float sum{0};
  for (const Boid& boid : stormo) {
    sum += distanza(boid.get_pos(), {0, 0});
  }
  return sum / static_cast<float>((stormo.size()));
}

float standdev_position(std::vector<Boid> const& stormo)
{
  if (stormo.size() < 3) {
    throw std::runtime_error{
        "Non ci sono abbastanza uccelli per calcolare i parametri medi"};
  }
  float sum{0};
  const float mean_pos{mean_position(stormo)};
  for (const Boid& boid : stormo) {
    sum += powf((distanza(boid.get_pos(), {0, 0}) - mean_pos), 2);
  }
  return std::sqrt(sum / static_cast<float>((stormo.size() - 1)));
}

float mean_velocity(std::vector<Boid> const& stormo)
{
  if (stormo.size() < 3) {
    throw std::runtime_error{
        "Non ci sono abbastanza uccelli per calcolare i parametri medi"};
  }
  float sum{0};
  for (const Boid& boid : stormo) {
    sum += distanza(boid.get_vel(), {0, 0});
  }
  return sum / static_cast<float>((stormo.size()));
}

float standdev_velocity(std::vector<Boid> const& stormo)
{
  if (stormo.size() < 3) {
    throw std::runtime_error{
        "Non ci sono abbastanza uccelli per calcolare i parametri medi"};
  }
  float sum{0};
  const float mean_vel{mean_velocity(stormo)};
  for (const Boid& boid : stormo) {
    sum += powf((distanza(boid.get_vel(), {0, 0}) - mean_vel), 2);
  }
  return std::sqrt(sum / static_cast<float>((stormo.size() - 1)));
}

float mean_distance(std::vector<Boid> const& stormo)
{
  if (stormo.size() < 3) {
    throw std::runtime_error{
        "Non ci sono abbastanza uccelli per calcolare i parametri medi"};
  }
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
  if (stormo.size() < 3) {
    throw std::runtime_error{
        "Non ci sono abbastanza uccelli per calcolare i parametri medi"};
  }
  float sum{0};
  const float mean_dist{mean_distance(stormo)};
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    for (unsigned long int j{0}; j != i; ++j) {
      sum += powf(
          (distanza(stormo[i].get_pos(), stormo[j].get_pos()) - mean_dist), 2);
    }
  }
  return std::sqrt(sum
                   / ((static_cast<float>(stormo.size())
                       * (static_cast<float>(stormo.size()) - 1))
                          / 2.0f
                      - 1.0f));
}
} // namespace pf