#ifndef POINT2D_HPP
#define POINT2D_HPP

#include <cmath>

namespace pf {
struct Point2D
{
  double x;
  double y;
};

inline double lunghezza(Point2D const& a)
{
  return std::sqrt(a.x * a.x + a.y * a.y);
}

inline Point2D normalizzazione(Point2D const& a)
{
  double len = lunghezza(a);
  if (len == 0) {
    return a;
  } else {
    return {a.x / len, a.y / len};
  }
}

inline double dot(Point2D const& a, Point2D const& b)
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

inline Point2D operator*(double u, Point2D const& a)
{
  return {u * a.x, u * a.y};
}

inline Point2D operator/(Point2D const& a, double u)
{
  return {a.x / u, a.y / u};
}

inline double distanza(Point2D const& a, Point2D const& b)
{
  return std::sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

} // namespace pf

#endif // POINT2D_HPP