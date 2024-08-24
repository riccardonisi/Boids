#ifndef BOIDS_HPP
#define BOIDS_HPP

#include "Point2D.hpp"
#include <vector>

namespace pf {

class Boid
{
  Point2D pos_;
  Point2D vel_;

 public:
  explicit Boid(Point2D p, Point2D v)
      : pos_{p}
      , vel_{v}
  {}
  const Point2D& get_pos() const;

  const Point2D& get_vel() const;

  void set_pos(Point2D p);

  void set_vel(Point2D v);
};

double dot(Point2D const& a, Point2D const& b);

bool operator==(Boid const& a, Boid const& b);

bool campo_visivo(Boid const& a, Boid const& b, double angolo);

Point2D separazione(std::vector<Boid> const& stormo, unsigned long int i,
                    double s, double ds, double angolo);

Point2D allineamento(std::vector<Boid> const& stormo, unsigned long int i,
                     double a, double d, double angolo);

Point2D coesione(std::vector<Boid> const& stormo, unsigned long int i, double c,
                 double d, double angolo);

std::vector<Boid> genera_stormo(double n);

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

void movimento(std::vector<Boid>& stormo, double t);

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
                         double s, double a, double c, double angolo);

void comportamento_bordi(std::vector<Boid>& stormo);

void controllo_velocità(std::vector<Boid>& stormo, double v);

Point2D separazione_altro_stormo(std::vector<Boid> const& stormo,
                                 Boid const& uccello, double s, double ds,
                                 double angolo);

void applicazione_regole_due_stormi(std::vector<Boid>& stormo,
                                    std::vector<Boid> const& stormo_altro,
                                    double d, double ds, double s, double a,
                                    double c, double ds2, double s2,
                                    double angolo);
} // namespace pf
#endif