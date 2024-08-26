#include "statistics.hpp"
#include <SFML/Graphics.hpp>

namespace pf {

sf::Vector2f realeToPixel(float x, float y, float scaleFactorX,
                          float scaleFactorY);

float calculateRotationAngle(float dx, float dy);

void simulazione_piano(int n, float d, float ds, float s, float a, float c,
                       float angolo);

void simulazione_piano_due_stormi(int n1, int n2, float d, float ds, float s,
                                  float a, float c, float ds2, float s2,
                                  float angolo);

sf::Vector2f set_graph_point(int i, float valore, int size, float scaleFactorX,
                             float scaleFactorY, float max_y);

void grafici(int n, float d, float ds, float s, float a, float c, float angolo);

} // namespace pf