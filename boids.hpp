#ifndef BOIDS_HPP
#define BOIDS_HPP

#include <cassert>
#include <iostream>
#include <numeric>
#include <random>
#include <stdexcept>
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
  Point2D pos() const
  {
    return pos_;
  }
  Point2D vel() const
  {
    return vel_;
  }
};

bool operator==(Boid const& a, Boid const& b)
{
  if (a.pos().x == b.pos().x && a.pos().y == b.pos().y && a.vel().x == b.vel().x
      && a.vel().y == b.vel().y) {
    return true;
  } else {
    return false;
  }
};

Point2D separazione(std::vector<Boid> const& stormo, int i, double s)
{
  int n = static_cast<int>(stormo.size());
  if (n < 2) {
    throw std::runtime_error{
        "Non ci sono abbastanza uccelli per applicare le regole di volo"};
  }
  Point2D sum{0, 0};
  for (int j{0}; j != n; ++j) {
    Point2D const& p = stormo[static_cast<long unsigned int>(j)].pos();
    sum = sum + p - stormo[static_cast<long unsigned int>(i)].pos();
  }
  return -s * sum; // questo è il termine correttivo v1
}

Point2D allineamento(std::vector<Boid> const& stormo, int i, double a)
{
  int n = static_cast<int>(stormo.size());
  if (n < 2) {
    throw std::runtime_error{
        "Non ci sono abbastanza uccelli per applicare le regole di volo"};
  }
  Point2D sum{0, 0};
  for (int j{0}; j != n; ++j) {
    if (j != i) {
      Point2D const& v = stormo[static_cast<long unsigned int>(j)].vel();
      sum              = sum + v;
    }
  }
  return a * (sum / (n - 1) - stormo[static_cast<long unsigned int>(i)].vel());
}

Point2D coesione(std::vector<Boid> const& stormo, int i, double c)
{
  int n = static_cast<int>(stormo.size());
  if (stormo.size() < 2) {
    throw std::runtime_error{
        "Non ci sono abbastanza uccelli per applicare le regole di volo"};
  }
  Point2D sum{0, 0};
  for (int j{0}; j != n; ++j) {
    if (j != i) {
      Point2D const& p = stormo[static_cast<long unsigned int>(j)].pos();
      sum              = sum + p;
    }
  }
  return c * (sum / (n - 1) - stormo[static_cast<long unsigned int>(i)].pos());
}

std::vector<Boid> genera_stormo(double n)
{
  if (n < 1) {
    throw std::runtime_error{
        "Non ci sono abbastanza uccelli per generare lo stormo"};
  }
  if (std::floor(n) != n) {
    throw std::runtime_error{
        "Il numero di uccelli deve essere un numero naturale"};
  }
  std::vector<Boid> stormo;
  for (int i{0}; i < n; ++i) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    Boid x{{dis(gen), dis(gen)}, {dis(gen), dis(gen)}};
    stormo.push_back(x);
  }
  return stormo;
}

} // namespace pf
#endif