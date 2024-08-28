#ifndef BOIDS_HPP
#define BOIDS_HPP

#include "point2D.hpp"
#include <vector>

namespace pf {

constexpr float pi_f = 3.14159265358979323846f;

class Boid
{
  Point2D pos_;
  Point2D vel_;

 public:
  Boid(Point2D p, Point2D v)
      : pos_{p}
      , vel_{v}
  {}
  const Point2D& get_pos() const;

  const Point2D& get_vel() const;

  void set_pos(Point2D& p);

  void set_vel(Point2D& v);
};

bool operator==(Boid const& a, Boid const& b);

bool is_in_field_of_view(Boid const& a, Boid const& b, float field_of_view);

std::vector<Boid> generate_flock(double n);

Point2D separation(std::vector<Boid> const& flock, Boid const& boid, float s,
                   float ds, float field_of_view);

Point2D alignment(std::vector<Boid> const& flock, Boid const& boid, float a,
                  float d, float field_of_view);

Point2D cohesion(std::vector<Boid> const& flock, Boid const& boid, float c,
                 float d, float field_of_view);

void movement(std::vector<Boid>& flock, float t);

void boundary_behavior(std::vector<Boid>& flock);

void flocking_behavior(std::vector<Boid>& flock, float d, float ds, float s,
                       float a, float c, float field_of_view);

void random_boost(std::vector<Boid>& flock, float boost,
                  float turn_probability);

void speed_control(std::vector<Boid>& flock, float v);

void flocking_behavior_two_flocks(std::vector<Boid>& flock,
                                  std::vector<Boid> const& flock_other, float d,
                                  float ds, float s, float a, float c,
                                  float ds2, float s2, float field_of_view);
} // namespace pf
#endif