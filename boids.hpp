#ifndef BOIDS_HPP
#define BOIDS_HPP

#include <cassert>
#include <cmath>
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
double distanza(Point2D const& a, Point2D const& b)
{
  return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
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

Point2D separazione(std::vector<Boid> const& stormo, unsigned long int i,
                    double s)
{
  unsigned long int n = stormo.size();
  if (n < 2) {
    throw std::runtime_error{
        "Non ci sono abbastanza uccelli per applicare le regole di volo"};
  }
  Point2D sum{0, 0};
  for (unsigned long int j{0}; j != n; ++j) {
    Point2D const& p = stormo[j].pos();
    sum              = sum + p - stormo[i].pos();
  }
  return -s * sum; // questo è il termine correttivo v1
}

Point2D allineamento(std::vector<Boid> const& stormo, unsigned long int i,
                     double a)

{
  unsigned long int n = stormo.size();
  if (n < 2) {
    throw std::runtime_error{
        "Non ci sono abbastanza uccelli per applicare le regole di volo"};
  }
  Point2D sum{0, 0};
  for (unsigned long int j{0}; j != n; ++j) {
    if (j != i) {
      Point2D const& v = stormo[j].vel();
      sum              = sum + v;
    }
  }
  return a * (sum / static_cast<double>(n - 1) - stormo[i].vel());
}

Point2D coesione(std::vector<Boid> const& stormo, unsigned long int i, double c)
{
  unsigned long int n = stormo.size();
  if (stormo.size() < 2) {
    throw std::runtime_error{
        "Non ci sono abbastanza uccelli per applicare le regole di volo"};
  }
  Point2D sum{0, 0};
  for (unsigned long int j{0}; j != n; ++j) {
    if (j != i) {
      Point2D const& p = stormo[j].pos();
      sum              = sum + p;
    }
  }
  return c * (sum / static_cast<double>(n - 1) - stormo[i].pos());
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
  for (int i{0}; i != n; ++i) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    Boid x{{dis(gen), dis(gen)}, {dis(gen), dis(gen)}};
    stormo.push_back(x);
  }
  return stormo;
}
std::vector<Boid> boid_vicini(std::vector<Boid> const& stormo,
                              unsigned long int i, double d)
{
  unsigned long int n = stormo.size();
  std::vector<Boid> stormo_vicino;
  for (unsigned long int j{0}; j != n; ++j) {
    if (distanza(stormo[j].pos(), stormo[i].pos()) < d && i != j) {
      stormo_vicino.push_back(stormo[j]);
    }
  }
  return stormo_vicino;
}
void movimento(std::vector<Boid>& stormo, double t)
{
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    stormo[i].pos() = stormo[i].pos() + t * stormo[i].vel();
  }
}
void applicazione_regole(std::vector<Boid>& stormo, double d, double ds,
                         double s, double a, double c)
{
  std::vector<Point2D> correzione_velocità;
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    std::vector<Boid> stormo_vicino      = boid_vicini(stormo, i, d);
    std::vector<Boid> stormo_vicinissimo = boid_vicini(stormo, i, ds);
    correzione_velocità.push_back(separazione(stormo_vicinissimo, i, s)
                                  + allineamento(stormo_vicino, i, a)
                                  + coesione(stormo_vicino, i, c));
  }
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    stormo[i].vel() = stormo[i].vel() + correzione_velocità[i];
  }
}

} // namespace pf
#endif