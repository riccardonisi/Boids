#ifndef POINT2D_HPP
#define POINT2D_HPP

#include <cmath>

namespace pf {
struct Point2D
{
  float x;
  float y;
};

inline float lunghezza(Point2D const& a)
{
  return std::sqrt(a.x * a.x + a.y * a.y);
}

inline Point2D normalizzazione(Point2D const& a)
{
  float len = lunghezza(a);
  if (len == 0) {
    return a;
  } else {
    return {a.x / len, a.y / len};
  }
}

inline float dot(Point2D const& a, Point2D const& b)
{
  return a.x * b.x + a.y * b.y;
}

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
  return {a.x / u, a.y / u};
}

inline float distanza(Point2D const& a, Point2D const& b)
{
  return std::sqrtf(powf((a.x - b.x), 2) + powf((a.y - b.y), 2));
}

} // namespace pf

#endif // POINT2D_HPP