#ifndef BOIDS_HPP
#define BOIDS_HPP

#include <numeric>
#include <vector>

namespace pf {
struct Point2D
{
  double x;
  double y;
};
Point2D operator+(Point2D const& a, Point2D const& b)
{
  return {a.x + b.x, a.y + b.y};
}
Point2D operator-(Point2D const& a, Point2D const& b)
{
  return {a.x - b.x, a.y - b.y};
}
Point2D operator*(double u, Point2D const& a)
{
  return {u * a.x, u * a.y};
}

Point2D operator/(Point2D const& a, double u)
{
  return {a.x / u, a.y / u};
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
  Point2D const& pos()
  {
    return pos_;
  }
  Point2D const& vel()
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
  return -s * sum; // questo è il termine correttivo v1
}

Point2D allineamento(std::vector<Boid> stormo, int const& i, double a)
{
  Point2D sum{0, 0};
  for (int j{0}, n = stormo.size(); j != n; ++j) {
    if (j != i) {
      sum = sum + stormo[j].vel();
    }
  }
  return a
       * (sum / (stormo.size() - 1)
          - stormo[i].vel()); // questo è il termine correttivo v2
}

} // namespace pf
#endif