#include "statistics.hpp"

namespace pf {

float mean_position(std::vector<Boid> const& flock)
{
  if (flock.size() < 3) {
    throw std::runtime_error{
        "Not enough boids to estimate parameters"};
  }
  float sum{0};
  for (const Boid& boid : flock) {
    sum += distance(boid.get_pos(), {0, 0});
  }
  return sum / static_cast<float>((flock.size()));
}

float standdev_position(std::vector<Boid> const& flock)
{
  if (flock.size() < 3) {
    throw std::runtime_error{
        "Not enough boids to estimate parameters"};
  }
  float sum{0};
  const float mean_pos{mean_position(flock)};
  for (const Boid& boid : flock) {
    sum += powf((distance(boid.get_pos(), {0, 0}) - mean_pos), 2);
  }
  return std::sqrt(sum / static_cast<float>((flock.size() - 1)));
}

float mean_velocity(std::vector<Boid> const& flock)
{
  if (flock.size() < 3) {
    throw std::runtime_error{
        "Not enough boids to estimate parameters"};
  }
  float sum{0};
  for (const Boid& boid : flock) {
    sum += distance(boid.get_vel(), {0, 0});
  }
  return sum / static_cast<float>((flock.size()));
}

float standdev_velocity(std::vector<Boid> const& flock)
{
  if (flock.size() < 3) {
    throw std::runtime_error{
        "Not enough boids to estimate parameters"};
  }
  float sum{0};
  const float mean_vel{mean_velocity(flock)};
  for (const Boid& boid : flock) {
    sum += powf((distance(boid.get_vel(), {0, 0}) - mean_vel), 2);
  }
  return std::sqrt(sum / static_cast<float>((flock.size() - 1)));
}

float mean_distance(std::vector<Boid> const& flock)
{
  if (flock.size() < 3) {
    throw std::runtime_error{
        "Not enough boids to estimate parameters"};
  }
  float sum{0};
  for (unsigned long int i{0}; i != flock.size(); ++i) {
    for (unsigned long int j{0}; j != i; ++j) {
      sum += distance(flock[i].get_pos(), flock[j].get_pos());
    }
  }
  return 2.0f * sum
       / (static_cast<float>(flock.size())
          * (static_cast<float>(flock.size()) - 1));
}

float standdev_distance(std::vector<Boid> const& flock)
{
  if (flock.size() < 3) {
    throw std::runtime_error{
        "Not enough boids to estimate parameters"};
  }
  float sum{0};
  const float mean_dist{mean_distance(flock)};
  for (unsigned long int i{0}; i != flock.size(); ++i) {
    for (unsigned long int j{0}; j != i; ++j) {
      sum += powf(
          (distance(flock[i].get_pos(), flock[j].get_pos()) - mean_dist), 2);
    }
  }
  return std::sqrt(sum
                   / ((static_cast<float>(flock.size())
                       * (static_cast<float>(flock.size()) - 1))
                          / 2.0f
                      - 1.0f));
}
} // namespace pf