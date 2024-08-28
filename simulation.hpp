#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "statistics.hpp"
#include <SFML/Graphics.hpp>

namespace pf {

inline sf::Vector2f realeToPixel(float x, float y, float scaleFactorX,
                                 float scaleFactorY)
{
  return sf::Vector2f(x * scaleFactorX, y * scaleFactorY);
}

inline float calculateRotationAngle(float dx, float dy)
{
  return std::atan2(dy, dx) * 180.0f / pi_f; // In gradi
}

inline sf::Vector2f set_graph_point(int i, float valore, int size,
                                    float scaleFactorX, float scaleFactorY,
                                    float max_y)
{
  float y = valore / max_y;
  float x = static_cast<float>(i) / static_cast<float>(size);
  return sf::Vector2f(realeToPixel(x, 1.f - y, scaleFactorX, scaleFactorY));
}

void simulazione_piano(double n, float d, float ds, float s, float a, float c,
                       float angolo);

void simulazione_piano_due_stormi(double n1, double n2, float d, float ds, float s,
                                  float a, float c, float ds2, float s2,
                                  float angolo);

void grafici(double n, float d, float ds, float s, float a, float c, float angolo);

} // namespace pf

#endif