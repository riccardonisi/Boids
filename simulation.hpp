#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "statistics.hpp"
#include <SFML/Graphics.hpp>

namespace pf {

inline sf::Vector2f real_to_pixel(float x, float y, float scale_factor_x,
                                 float scale_factor_y)
{
  return sf::Vector2f(x * scale_factor_x, y * scale_factor_y);
}

inline float calculate_rotation_angle(float direction_x, float direction_y)
{
  return std::atan2(direction_y, direction_x) * 180.0f / pi_f; // In gradi
}

inline sf::Vector2f set_graph_point(int i, float value_y, int size,
                                    float scale_factor_x, float scale_factor_y,
                                    float max_y)
{
  float y = value_y / max_y;
  float x = static_cast<float>(i) / static_cast<float>(size);
  return sf::Vector2f(real_to_pixel(x, 1.f - y, scale_factor_x, scale_factor_y));
}

void simulation_one_flock(double n, float d, float ds, float s, float a, float c,
                       float field_of_view);

void simulation_two_flocks(double n1, double n2, float d, float ds, float s,
                                  float a, float c, float ds2, float s2,
                                  float field_of_view);

void graphs(double n, float d, float ds, float s, float a, float c, float field_of_view);

} // namespace pf

#endif