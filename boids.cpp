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
void Boid::set_pos(Point2D& p)
{
  pos_ = p;
}
void Boid::set_vel(Point2D& v)
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
  if (a == b) {
    return false;
  } else if (a.get_vel().x == 0.f && a.get_vel().x == 0.f) {
    return true;
  } else {
    Point2D direction    = normalization(a.get_vel());
    Point2D dir_to_other = normalization(b.get_pos() - a.get_pos());
    float dotProduct     = dot(direction, dir_to_other);
    float angle_between  = std::acos(dotProduct) * 180.0f / pi_f;
    return angle_between <= (field_of_view / 2.0f);
  }
}

std::vector<Boid> generate_flock(double n)
{
  if (n < 1) {
    throw std::runtime_error{"Not enought boids to generate a flock"};
  }
  if (std::floor(n) != n) {
    throw std::runtime_error{"The number of boids must be a natural number"};
  }
  std::vector<Boid> flock;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dis(0.0f, 1.0f);
  std::uniform_real_distribution<float> dis2(-1.0f, 1.0f);
  for (int i{0}; i != static_cast<int>(n); ++i) {
    Point2D p{dis(gen), dis(gen)};
    Point2D v{dis2(gen), dis2(gen)};
    Boid x{p, v};
    flock.push_back(x);
  }
  return flock;
}

Point2D separation(std::vector<Boid> const& flock, Boid const& boid, float s,
                   float ds, float field_of_view)
{
  auto n = flock.size();
  if (n < 2) {
    throw std::runtime_error{"Not enough boids to apply the rules of flight"};
  }
  Point2D sum{0, 0};
  for (Boid const& boid_other : flock) {
    if (distance(boid_other.get_pos(), boid.get_pos()) < ds
        && is_in_field_of_view(boid_other, boid, field_of_view)) {
      Point2D const& p = boid_other.get_pos();
      sum              = sum + p - boid.get_pos();
    }
  }
  return -s * sum;
}

Point2D alignment(std::vector<Boid> const& flock, Boid const& boid, float a,
                  float d, float field_of_view)
{
  int n{0};
  if (flock.size() < 2) {
    throw std::runtime_error{"Not enough boids to apply the rules of flight"};
  }
  Point2D sum{0, 0};
  for (Boid const& boid_other : flock) {
    if (distance(boid_other.get_pos(), boid.get_pos()) < d
        && is_in_field_of_view(boid_other, boid, field_of_view)) {
      ++n;
      Point2D const& v = boid_other.get_vel();
      sum              = sum + v;
    }
  }
  if (n != 0) {
    return a * (sum / static_cast<float>(n) - boid.get_vel());
  } else {
    return {0, 0};
  }
}

Point2D cohesion(std::vector<Boid> const& flock, Boid const& boid, float c,
                 float d, float field_of_view)
{
  int n{0};
  if (flock.size() < 2) {
    throw std::runtime_error{"Not enough boids to apply the rules of flight"};
  }
  Point2D sum{0, 0};
  for (Boid const& boid_other : flock) {
    if (distance(boid_other.get_pos(), boid.get_pos()) < d
        && is_in_field_of_view(boid_other, boid, field_of_view)) {
      ++n;
      Point2D const& p = boid_other.get_pos();
      sum              = sum + p;
    }
  }
  if (n != 0) {
    return c * (sum / static_cast<float>(n) - boid.get_pos());
  } else {
    return {0, 0};
  }
}

void movement(std::vector<Boid>& flock, float t)
{
  for (Boid& boid : flock) {
    Point2D new_pos = boid.get_pos() + t * boid.get_vel();
    boid.set_pos(new_pos);
  }
}

void boundary_behavior(std::vector<Boid>& flock)
{
  for (Boid& boid : flock) {
    if (boid.get_pos().x > 1) {
      Point2D new_pos{0, boid.get_pos().y};
      boid.set_pos(new_pos);
    }
    if (boid.get_pos().y > 1) {
      Point2D new_pos{boid.get_pos().x, 0};
      boid.set_pos(new_pos);
    }
    if (boid.get_pos().x < 0) {
      Point2D new_pos{1, boid.get_pos().y};
      boid.set_pos(new_pos);
    }
    if (boid.get_pos().y < 0) {
      Point2D new_pos{boid.get_pos().x, 1};
      boid.set_pos(new_pos);
    }
  }
}

void flocking_behavior(std::vector<Boid>& flock, float d, float ds, float s,
                       float a, float c, float field_of_view)
{
  std::vector<Point2D> vel_corrections;
  for (Boid const& boid : flock) {
    vel_corrections.push_back(separation(flock, boid, s, ds, field_of_view)
                              + alignment(flock, boid, a, d, field_of_view)
                              + cohesion(flock, boid, c, d, field_of_view));
  }
  for (unsigned long int i{0}; i != flock.size(); ++i) {
    Point2D new_vel = flock[i].get_vel() + vel_corrections[i];
    flock[i].set_vel(new_vel);
  }
}

void random_boost(std::vector<Boid>& flock, float boost, float turn_probability)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> prob_dis(0.0f, 1.0f);
  std::uniform_real_distribution<float> angle_dis(-pi_f / 8, pi_f / 8);

  for (pf::Boid& boid : flock) {
    Point2D current_vel = boid.get_vel();
    float current_speed = magnitude(current_vel);
    float new_speed     = current_speed + boost;
    float current_angle = std::atan2(current_vel.y, current_vel.x);

    float turn_angle = 0.0f;
    if (prob_dis(gen) < turn_probability) {
      turn_angle = angle_dis(gen);
    }

    float new_angle = current_angle + turn_angle;

    Point2D new_vel;
    new_vel.x = std::cos(new_angle) * new_speed;
    new_vel.y = std::sin(new_angle) * new_speed;

    boid.set_vel(new_vel);
  }
}

void speed_control(std::vector<Boid>& flock, float v)
{
  for (Boid& boid : flock) {
    if (boid.get_vel().x > v) {
      Point2D new_vel{v, boid.get_vel().y};
      boid.set_vel(new_vel);
    }
    if (boid.get_vel().y > v) {
      Point2D new_vel{boid.get_vel().x, v};
      boid.set_vel(new_vel);
    }
    if (boid.get_vel().x < -v) {
      Point2D new_vel{-v, boid.get_vel().y};
      boid.set_vel(new_vel);
    }
    if (boid.get_vel().y < -v) {
      Point2D new_vel{boid.get_vel().x, -v};
      boid.set_vel(new_vel);
    }
  }
}

void flocking_behavior_two_flocks(std::vector<Boid>& flock,
                                  std::vector<Boid> const& flock_other, float d,
                                  float ds, float s, float a, float c,
                                  float ds2, float s2, float field_of_view)
{
  std::vector<Point2D> vel_corrections;
  for (Boid const& boid : flock) {
    vel_corrections.push_back(
        separation(flock, boid, s, ds, field_of_view)
        + separation(flock_other, boid, s2, ds2, field_of_view)
        + alignment(flock, boid, a, d, field_of_view)
        + cohesion(flock, boid, c, d, field_of_view));
  }
  for (unsigned long int i{0}; i != flock.size(); ++i) {
    Point2D new_vel = flock[i].get_vel() + vel_corrections[i];
    flock[i].set_vel(new_vel);
  }
}

} // namespace pf