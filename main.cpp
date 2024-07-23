#include "boids.hpp"
#include <iostream>
int main()
{
  std::vector<pf::Boid> prova;
  pf::Point2D p1{2., 3.};
  pf::Point2D v1{0, 0};
  pf::Point2D p2{4.5, 7.8};
  pf::Point2D v2{0, 0};
  pf::Boid b1{p1, v1};
  pf::Boid b2{p2, v2};
  prova.push_back(b1);
  prova.push_back(b2);
 pf::Point2D v3= separazione(prova, p1, 0.5);
  std::cout << v3.x << " "<< v3.y;
}