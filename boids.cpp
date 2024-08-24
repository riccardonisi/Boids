#include "boids.hpp"

namespace pf {
const Point2D& Boid::get_pos() const
{
  return pos_;
}
const Point2D& Boid::get_vel() const
{
  return vel_;
}
void Boid::set_pos(Point2D p)
{
  pos_ = p;
}
void Boid::set_vel(Point2D v)
{
  vel_ = v;
}

bool operator==(Boid const& a, Boid const& b)
{
  if (a.get_pos().x == b.get_pos().x && a.get_pos().y == b.get_pos().y
      && a.get_vel().x == b.get_vel().x && a.get_vel().y == b.get_vel().y) {
    return true;
  } else {
    return false;
  }
}

bool campo_visivo(Boid const& a, Boid const& b, double angolo)
{
  Point2D direzione       = normalizzazione(a.get_vel());
  Point2D dir_verso_altro = normalizzazione(b.get_pos() - a.get_pos());
  double dotProduct       = dot(direzione, dir_verso_altro);
  double angle            = std::acos(dotProduct) * 180.0 / M_PI;
  return angle <= angolo / 2.0;
}

Point2D separazione(std::vector<Boid> const& stormo, unsigned long int i,
                    double s, double ds, double angolo)
{
  unsigned long int n = stormo.size();
  if (n < 2) {
    throw std::runtime_error{
        "Non ci sono abbastanza uccelli per applicare le regole di volo"};
  }
  Point2D sum{0, 0};
  for (unsigned long int j{0}; j != n; ++j) {
    if (distanza(stormo[j].get_pos(), stormo[i].get_pos()) < ds
        && campo_visivo(stormo[j], stormo[i], angolo) == true) {
      Point2D const& p = stormo[j].get_pos();
      sum              = sum + p - stormo[i].get_pos();
    }
  }
  return -s * sum; // questo è il termine correttivo v1
}

Point2D allineamento(std::vector<Boid> const& stormo, unsigned long int i,
                     double a, double d, double angolo)
{
  int n{0};
  if (stormo.size() < 2) {
    throw std::runtime_error{
        "Non ci sono abbastanza uccelli per applicare le regole di volo"};
  }
  Point2D sum{0, 0};
  for (unsigned long int j{0}; j != stormo.size(); ++j) {
    if (j != i && distanza(stormo[j].get_pos(), stormo[i].get_pos()) < d
        && campo_visivo(stormo[j], stormo[i], angolo) == true) {
      ++n;
      Point2D const& v = stormo[j].get_vel();
      sum              = sum + v;
    }
  }
  if (n != 0) {
    return a * (sum / static_cast<double>(n) - stormo[i].get_vel());
  } else {
    return {0, 0};
  }
}

Point2D coesione(std::vector<Boid> const& stormo, unsigned long int i, double c,
                 double d, double angolo)
{
  int n{0};
  if (stormo.size() < 2) {
    throw std::runtime_error{
        "Non ci sono abbastanza uccelli per applicare le regole di volo"};
  }
  Point2D sum{0, 0};
  for (unsigned long int j{0}; j != stormo.size(); ++j) {
    if (j != i && distanza(stormo[j].get_pos(), stormo[i].get_pos()) < d
        && campo_visivo(stormo[j], stormo[i], angolo) == true) {
      ++n;
      Point2D const& p = stormo[j].get_pos();
      sum              = sum + p;
    }
  }
  if (n != 0) {
    return c * (sum / static_cast<double>(n) - stormo[i].get_pos());
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
    std::uniform_real_distribution<> dis2(-1.0, 1.0);
    Boid x{{dis(gen), dis(gen)}, {dis2(gen), dis2(gen)}};
    stormo.push_back(x);
  }
  return stormo;
}

void movimento(std::vector<Boid>& stormo, double t)
{
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    stormo[i].set_pos(stormo[i].get_pos() + t * stormo[i].get_vel());
  }
}

void applicazione_regole(std::vector<Boid>& stormo, double d, double ds,
                         double s, double a, double c, double angolo)
{
  std::vector<Point2D> correzione_velocità;
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    correzione_velocità.push_back(separazione(stormo, i, s, ds, angolo)
                                  + allineamento(stormo, i, a, d, angolo)
                                  + coesione(stormo, i, c, d, angolo));
  }
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    stormo[i].set_vel(stormo[i].get_vel() + correzione_velocità[i]);
  }
}

void comportamento_bordi(std::vector<Boid>& stormo)
{
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    if (stormo[i].get_pos().x > 1) {
      stormo[i].set_pos({0, stormo[i].get_pos().y});
    }
    if (stormo[i].get_pos().y > 1) {
      stormo[i].set_pos({stormo[i].get_pos().x, 0});
    }
    if (stormo[i].get_pos().x < 0) {
      stormo[i].set_pos({1, stormo[i].get_pos().y});
    }
    if (stormo[i].get_pos().y < 0) {
      stormo[i].set_pos({stormo[i].get_pos().x, 1});
    }
  }
}

void controllo_velocità(std::vector<Boid>& stormo, double v)
{
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    if (stormo[i].get_vel().x > v) {
      stormo[i].set_vel({v, stormo[i].get_vel().y});
    }
    if (stormo[i].get_vel().y > v) {
      stormo[i].set_vel({stormo[i].get_vel().x, v});
    }
    if (stormo[i].get_vel().x < -v) {
      stormo[i].set_vel({-v, stormo[i].get_vel().y});
    }
    if (stormo[i].get_vel().y < -v) {
      stormo[i].set_vel({stormo[i].get_vel().x, -v});
    }

    if (abs(stormo[i].get_vel().x) < 0.3) {
      stormo[i].set_vel({0.3, stormo[i].get_vel().y});
    }
    if (abs(stormo[i].get_vel().y) < 0.3) {
      stormo[i].set_vel({stormo[i].get_vel().y, 0.3});
    }
  }
}

Point2D separazione_altro_stormo(std::vector<Boid> const& stormo,
                                 Boid const& uccello, double s, double ds,
                                 double angolo)
{
  unsigned long int n = stormo.size();
  if (n < 2) {
    throw std::runtime_error{
        "Non ci sono abbastanza uccelli per applicare le regole di volo"};
  }
  Point2D sum{0, 0};
  for (unsigned long int j{0}; j != n; ++j) {
    if (distanza(stormo[j].get_pos(), uccello.get_pos()) < ds) {
      Point2D const& p = stormo[j].get_pos();
      sum              = sum + p - uccello.get_pos();
    }
  }
  return -s * sum;
}

void applicazione_regole_due_stormi(std::vector<Boid>& stormo,
                                    std::vector<Boid> const& stormo_altro,
                                    double d, double ds, double s, double a,
                                    double c, double ds2, double s2,
                                    double angolo)
{
  std::vector<Point2D> correzione_velocità;
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    correzione_velocità.push_back(
        separazione(stormo, i, s, ds, angolo)
        + separazione_altro_stormo(stormo_altro, stormo[i], s2, ds2, angolo)
        + allineamento(stormo, i, a, d, angolo)
        + coesione(stormo, i, c, d, angolo));
  }
  for (unsigned long int i{0}; i != stormo.size(); ++i) {
    stormo[i].set_vel(stormo[i].get_vel() + correzione_velocità[i]);
  }
}

} // namespace pf