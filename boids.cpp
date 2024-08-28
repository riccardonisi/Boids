#include "boids.hpp"
#include <random>

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

bool is_in_field_of_view(Boid const& a, Boid const& b, float field_of_view)
{
  if (a.get_vel().x == 0.f && a.get_vel().x == 0.f) {
    return true;
  } else {
    Point2D direction       = normalization(a.get_vel());
    Point2D dir_to_other = normalization(b.get_pos() - a.get_pos());
    float dotProduct        = dot(direction, dir_to_other);
    float angle_between            = std::acos(dotProduct) * 180.0f / pi_f;
    return angle_between <= (field_of_view / 2.0f);
  }
}

Point2D separation(std::vector<Boid> const& flock, unsigned long int i,
                    float s, float ds, float field_of_view)
{
  unsigned long int n = flock.size();
  if (n < 2) {
    throw std::runtime_error{
        "Not enough boids to apply the rules of flight"};
  }
  Point2D sum{0, 0};
  for (unsigned long int j{0}; j != n; ++j) {
    if (distance(flock[j].get_pos(), flock[i].get_pos()) < ds
        && is_in_field_of_view(flock[j], flock[i], field_of_view)) {
      Point2D const& p = flock[j].get_pos();
      sum              = sum + p - flock[i].get_pos();
    }
  }
  return -s * sum;
}

Point2D alignment(std::vector<Boid> const& flock, unsigned long int i,
                     float a, float d, float field_of_view)
{
  int n{0};
  if (flock.size() < 2) {
    throw std::runtime_error{
        "Not enough boids to apply the rules of flight"};
  }
  Point2D sum{0, 0};
  for (unsigned long int j{0}; j != flock.size(); ++j) {
    if (j != i && distance(flock[j].get_pos(), flock[i].get_pos()) < d
        && is_in_field_of_view(flock[j], flock[i], field_of_view)) {
      ++n;
      Point2D const& v = flock[j].get_vel();
      sum              = sum + v;
    }
  }
  if (n != 0) {
    return a * (sum / static_cast<float>(n) - flock[i].get_vel());
  } else {
    return {0, 0};
  }
}

Point2D cohesion(std::vector<Boid> const& flock, unsigned long int i, float c,
                 float d, float field_of_view)
{
  int n{0};
  if (flock.size() < 2) {
    throw std::runtime_error{
        "Not enough boids to apply the rules of flight"};
  }
  Point2D sum{0, 0};
  for (unsigned long int j{0}; j != flock.size(); ++j) {
    if (j != i && distance(flock[j].get_pos(), flock[i].get_pos()) < d
        && is_in_field_of_view(flock[j], flock[i], field_of_view)) {
      ++n;
      Point2D const& p = flock[j].get_pos();
      sum              = sum + p;
    }
  }
  if (n != 0) {
    return c * (sum / static_cast<float>(n) - flock[i].get_pos());
  } else {
    return {0, 0};
  }
}

std::vector<Boid> generate_flock(double n)
{
  if (n < 1) {
    throw std::runtime_error{
        "Not enought boids to generate a flock"};
  }
  if (std::floor(n) != n) {
    throw std::runtime_error{
        "The number of boids must be a natural number"};
  }
  std::vector<Boid> flock;
  std::random_device rd;
  std::mt19937 gen(rd());
  for (int i{0}; i != static_cast<int>(n); ++i) {
    std::uniform_real_distribution<float> dis(0.0f, 1.0f);
    std::uniform_real_distribution<float> dis2(-1.0f, 1.0f);
    Point2D p{dis(gen), dis(gen)};
    Point2D v{dis2(gen), dis2(gen)};
    Boid x{p, v};
    flock.push_back(x);
  }
  return flock;
}

void movement(std::vector<Boid>& flock, float t)
{
  for (unsigned long int i{0}; i != flock.size(); ++i) {
    flock[i].set_pos(flock[i].get_pos() + t * flock[i].get_vel());
  }
}

void random_boost(std::vector<Boid>& flock, float boost,
                  float turn_probability)
{
  std::random_device rd;
  std::mt19937 gen(rd());

  for (pf::Boid& boid : flock) {
    Point2D current_vel = boid.get_vel();
    float current_speed = magnitude(current_vel);

    float new_speed = current_speed + boost;

    float current_angle = std::atan2(current_vel.y, current_vel.x);

    std::uniform_real_distribution<float> prob_dis(0.0f, 1.0f);
    float turn_angle = 0.0f;
    if (prob_dis(gen) < turn_probability) {
      std::uniform_real_distribution<float> angle_dis(-pi_f / 8, pi_f / 8);
      turn_angle = angle_dis(gen);
    }

    float new_angle = current_angle + turn_angle;

    Point2D new_vel;
    new_vel.x = std::cos(new_angle) * new_speed;
    new_vel.y = std::sin(new_angle) * new_speed;

    boid.set_vel(new_vel);
  }
}

void flocking_behavior(std::vector<Boid>& flock, float d, float ds, float s,
                         float a, float c, float field_of_view)
{
  std::vector<Point2D> vel_corrections;
  for (unsigned long int i{0}; i != flock.size(); ++i) {
    vel_corrections.push_back(separation(flock, i, s, ds, field_of_view)
                                  + alignment(flock, i, a, d, field_of_view)
                                  + cohesion(flock, i, c, d, field_of_view));
  }
  for (unsigned long int i{0}; i != flock.size(); ++i) {
    flock[i].set_vel(flock[i].get_vel() + vel_corrections[i]);
  }
}

void boundary_behavior(std::vector<Boid>& flock)
{
  for (unsigned long int i{0}; i != flock.size(); ++i) {
    if (flock[i].get_pos().x > 1) {
      flock[i].set_pos({0, flock[i].get_pos().y});
    }
    if (flock[i].get_pos().y > 1) {
      flock[i].set_pos({flock[i].get_pos().x, 0});
    }
    if (flock[i].get_pos().x < 0) {
      flock[i].set_pos({1, flock[i].get_pos().y});
    }
    if (flock[i].get_pos().y < 0) {
      flock[i].set_pos({flock[i].get_pos().x, 1});
    }
  }
}

void speed_control(std::vector<Boid>& flock, float v)
{
  for (unsigned long int i{0}; i != flock.size(); ++i) {
    if (flock[i].get_vel().x > v) {
      flock[i].set_vel({v, flock[i].get_vel().y});
    }
    if (flock[i].get_vel().y > v) {
      flock[i].set_vel({flock[i].get_vel().x, v});
    }
    if (flock[i].get_vel().x < -v) {
      flock[i].set_vel({-v, flock[i].get_vel().y});
    }
    if (flock[i].get_vel().y < -v) {
      flock[i].set_vel({flock[i].get_vel().x, -v});
    }
  }
}

Point2D separation_between_flocks(std::vector<Boid> const& flock,
                                 Boid const& boid, float s, float ds,
                                 float field_of_view)
{
  unsigned long int n = flock.size();
  if (n < 2) {
    throw std::runtime_error{
        "Not enough boids to apply the rules of flight"};
  }
  Point2D sum{0, 0};
  for (unsigned long int j{0}; j != n; ++j) {
    if (distance(flock[j].get_pos(), boid.get_pos()) < ds
        && is_in_field_of_view(flock[j], boid, field_of_view)) {
      Point2D const& p = flock[j].get_pos();
      sum              = sum + p - boid.get_pos();
    }
  }
  return -s * sum;
}

void flocking_behavior_two_flocks(std::vector<Boid>& flock,
                                    std::vector<Boid> const& flock_other,
                                    float d, float ds, float s, float a,
                                    float c, float ds2, float s2, float field_of_view)
{
  std::vector<Point2D> vel_corrections;
  for (unsigned long int i{0}; i != flock.size(); ++i) {
    vel_corrections.push_back(
        separation(flock, i, s, ds, field_of_view)
        + separation_between_flocks(flock_other, flock[i], s2, ds2, field_of_view)
        + alignment(flock, i, a, d, field_of_view)
        + cohesion(flock, i, c, d, field_of_view));
  }
  for (unsigned long int i{0}; i != flock.size(); ++i) {
    flock[i].set_vel(flock[i].get_vel() + vel_corrections[i]);
  }
}

} // namespace pf