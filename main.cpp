#include "boids.hpp"
#include <iostream>
#include <random>

int main()
{
 int n = 20;
 std::vector<pf::Boid> prova = pf::genera_stormo(n);
 std::cout << prova.size() << '\n';
 std::cout << prova[1].pos().x << ';' << prova[1].pos().y << ';'  << prova[1].vel().x << ';'  << prova[1].vel().y << '\n';
 /* for (int i{0}; i < n; ++i){
 std::cout << prova[i].pos().x << '\n'; 
} */
}
