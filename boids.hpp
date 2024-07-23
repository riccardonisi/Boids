#ifndef BOIDS_HPP
#define BOIDS_HPP

#include <vector>

namespace pf {
struct Point2D
{
  double x;
  double y;
};
Point2D operator-(Point2D const& a, Point2D const& b)
{
  return {a.x - b.x, a.y - b.y};
}
Point2D operator+(Point2D const& a, Point2D const& b)
{
  return {a.x + b.x, a.y + b.y};
}
Point2D operator*(double u, Point2D const& a)
{
  return {u * a.x, u * a.y};
}

class Boid
{
  Point2D pos_;
  Point2D vel_;

 public:
  Boid(Point2D p, Point2D v)
      : pos_{p}
      , vel_{v}
  {}
  Point2D pos()
  {
    return pos_;
  }
  Point2D vel()
  {
    return vel_;
  }
};

Point2D separazione(std::vector<Boid> stormo, Point2D const& pi, double s)
{
  Point2D sum{0, 0};
  for (int i{0}, n = stormo.size(); i != n; ++i) {
    auto const& p = stormo[i].pos();
    sum           = sum + p - pi;
  }
  return -s*sum; // questo è il termine correttivo v1
}

} // namespace pf
#endif