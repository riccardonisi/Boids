#include "boids.hpp"
#include <iostream>
#include <random>

int main()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);
  for (int n = 0; n < 50; ++n)
    std::cout << dis(gen) << ' ';
  std::cout << '\n';
}
