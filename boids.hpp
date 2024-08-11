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
  const Point2D& pos() const
  {
    return pos_;
  }
  const Point2D& vel() const
  {
    return vel_;
  }
  Point2D& pos2()
  {
    return pos_;
  }
  Point2D& vel2()
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
                    double s, double ds)
{
  unsigned long int n = stormo.size();
  if (n < 2) {
    throw std::runtime_error{
        "Non ci sono abbastanza uccelli per applicare le regole di volo"};
  }
  Point2D sum{0, 0};
  for (unsigned long int j{0}; j != n; ++j) {
    if (distanza(stormo[j].pos(), stormo[i].pos()) < ds) {
      Point2D const& p = stormo[j].pos();
      sum              = sum + p - stormo[i].pos();
    }
  }
  return -s * sum; // questo è il termine correttivo v1
}

Point2D allineamento(std::vector<Boid> const& stormo, unsigned long int i,
                     double a, double d)
{
  int n{0};
  if (stormo.size() < 2) {
    throw std::runtime_error{
        "Non ci sono abbastanza uccelli per applicare le regole di volo"};
  }
  Point2D sum{0, 0};
  for (unsigned long int j{0}; j != stormo.size(); ++j) {
    if (j != i && distanza(stormo[j].pos(), stormo[i].pos()) < d) {
      ++n;
      Point2D const& v = stormo[j].vel();
      sum              = sum + v;
    }
  }
  if (n != 0) {
    return a * (sum / static_cast<double>(n) - stormo[i].vel());
  } else {
    return {0, 0};
  }
}

Point2D coesione(std::vector<Boid> const& stormo, unsigned long int i, double c,
                 double d)
{
  int n{0};
  if (stormo.size() < 2) {
    throw std::runtime_error{
        "Non ci sono abbastanza uccelli per applicare le regole di volo"};
  }
  Point2D sum{0, 0};
  for (unsigned long int j{0}; j != stormo.size(); ++j) {
    if (j != i && distanza(stormo[j].pos(), stormo[i].pos()) < d) {
      ++n;
      Point2D const& p = stormo[j].pos();
      sum              = sum + p;
    }
  }
  if (n != 0) {
    return c * (sum / static_cast<double>(n) - stormo[i].pos());
  } else {
    return {0, 0};
  }
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

/*std::vector<Boid> boid_vicini(std::vector<Boid> const& stormo,
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
}*/

void movimento(std::vector<Boid>& stormo, double t)
{
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    stormo[i].pos2() = stormo[i].pos2() + t * stormo[i].vel();
  }
}

/*void applicazione_regole(std::vector<Boid>& stormo, double d, double ds,
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
}*/

void applicazione_regole(std::vector<Boid>& stormo, double d, double ds,
                         double s, double a, double c)
{
  std::vector<Point2D> correzione_velocità;
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    correzione_velocità.push_back(separazione(stormo, i, s, ds)
                                  + allineamento(stormo, i, a, d)
                                  + coesione(stormo, i, c, d));
  }
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    stormo[i].vel2() = stormo[i].vel2() + correzione_velocità[i];
  }
}
void comportamento_bordi(std::vector<Boid>& stormo)
{
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    if (stormo[i].pos().x > 1) {
      stormo[i].pos2().x = 0;
    }
    if (stormo[i].pos2().y > 1) {
      stormo[i].pos2().y = 0;
    }
    if (stormo[i].pos().x < 0) {
      stormo[i].pos2().x = 1;
    }
    if (stormo[i].pos().y < 0) {
      stormo[i].pos2().y = 1;
    }
  }
}
} // namespace pf
#endif