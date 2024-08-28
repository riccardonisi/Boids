#ifndef POINT2D_HPP
#define POINT2D_HPP

#include <cmath>
#include <stdexcept>

namespace pf {
struct Point2D
{
  float x;
  float y;
};

inline Point2D operator+(Point2D const& a, Point2D const& b)
{
  return {a.x + b.x, a.y + b.y};
}

inline Point2D operator-(Point2D const& a, Point2D const& b)
{
  return {a.x - b.x, a.y - b.y};
}

inline Point2D operator*(float u, Point2D const& a)
{
  return {u * a.x, u * a.y};
}

inline Point2D operator/(Point2D const& a, float u)
{
  if (u == 0) {
    throw std::runtime_error{"Cannot divide by 0"};
  }
  return {a.x / u, a.y / u};
}

inline float dot(Point2D const& a, Point2D const& b)
{
  return a.x * b.x + a.y * b.y;
}

inline float magnitude(Point2D const& a)
{
  return std::sqrt(a.x * a.x + a.y * a.y);
}

inline Point2D normalization(Point2D const& a)
{
  float length = magnitude(a);
  if (length == 0) {
    return a;
  } else {
    return {a.x / length, a.y / length};
  }
}

inline float distance(Point2D const& a, Point2D const& b)
{
  return std::sqrt(powf((a.x - b.x), 2) + powf((a.y - b.y), 2));
}

} // namespace pf

#endif // POINT2D_HPP