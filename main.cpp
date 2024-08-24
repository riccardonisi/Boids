/*#include "boids.hpp"
#include "statistics.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

// Funzione per convertire un valore reale in pixel
sf::Vector2f realeToPixel(float x, float y, float scaleFactorX,
                          float scaleFactorY)
{
  return sf::Vector2f(x * scaleFactorX, y * scaleFactorY);
}

int main()
{
  sf::RenderWindow window(
      sf::VideoMode(1000, 600),
      "Simulazione del comportamento di uno stormo, di Nisi, Rosini, Seren");
  constexpr int frame_rate{60};
  window.setFramerateLimit(frame_rate);

  // Esempio di vettore di posizioni reali
  std::vector<pf::Boid> stormo = pf::genera_stormo(100);

  // Fattori di scala per la conversione
  float scaleFactorX = 1000.0f / 1.0f;
  float scaleFactorY = 600.0f / 1.0f;

  // Eseguire il loop della finestra finché è aperta
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color::Cyan);

    // Disegnare i punti convertiti in pixel
    for (pf::Boid const& boid : stormo) {
      sf::Vector2f pixelPos =
          realeToPixel(boid.pos().x, boid.pos().y, scaleFactorX, scaleFactorY);
      sf::CircleShape shape(2.5);
      shape.setPointCount(3);
      shape.setPosition(pixelPos);
      shape.setFillColor(sf::Color::Black);
      window.draw(shape);
    }

    pf::movimento(stormo, 0.001);
    pf::comportamento_bordi(stormo);
    pf::applicazione_regole(stormo, 0.02, 0.005, 0.05, 0.15, 0.05);
    pf::controllo_velocità(stormo, 2);

    window.display();
  }

  return 0;
}
*/

#include "Point2D.hpp"
#include "boids.hpp"
#include "statistics.hpp"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include <memory>

// Funzione per convertire un valore reale in pixel
sf::Vector2f realeToPixel(float x, float y, float scaleFactorX,
                          float scaleFactorY)
{
  return sf::Vector2f(x * scaleFactorX, y * scaleFactorY);
}

float calculateRotationAngle(float dx, float dy)
{
  return std::atan2(dy, dx) * 180.0 / M_PI; // In gradi
}

void simulazione_piano(int n, double d, double ds, double s, double a, double c)
{
  constexpr int pixelx = 1000;
  constexpr int pixely = 600;
  sf::RenderWindow window(
      sf::VideoMode(pixelx, pixely),
      "Simulazione del comportamento di uno stormo, di Nisi, Rosini, Seren");
  constexpr int frame_rate{60};
  window.setFramerateLimit(frame_rate);

  // Esempio di vettore di posizioni reali
  std::vector<pf::Boid> stormo = pf::genera_stormo(n);

  // Fattori di scala per la conversione
  float scaleFactorX = static_cast<float>(pixelx) / 1.0f;
  float scaleFactorY = static_cast<float>(pixely) / 1.0f;

  // crea una texture (e poi una sprite) con lo sfondo
  sf::Texture texture;
  if (!texture.loadFromFile("sfondo.png")) {
    throw std::runtime_error{"Impossibile caricare l'immagine di sfondo"};
  }
  sf::Sprite sprite;
  sprite.setTexture(texture);

  // Eseguire il loop della finestra finché è aperta
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color::Cyan);
    window.draw(sprite);

    // Disegnare i punti convertiti in pixel
    for (pf::Boid const& boid : stormo) {
      sf::Vector2f pixelPos = realeToPixel(boid.get_pos().x, boid.get_pos().y,
                                           scaleFactorX, scaleFactorY);
      sf::ConvexShape triangle;
      triangle.setPointCount(3);
      triangle.setPoint(0, sf::Vector2f(0, -5.0)); // Vertice superiore (punta)
      triangle.setPoint(1,
                        sf::Vector2f(-3.0, 5.0)); // Punto a sinistra della base
      triangle.setPoint(2, sf::Vector2f(3.0, 5.0)); // Punto a destra della base
      triangle.setPosition(pixelPos);
      triangle.setFillColor(sf::Color::Black);
      triangle.setOrigin(0, -5.0);

      float targetAngle = calculateRotationAngle(boid.get_vel().norm().x,
                                                 boid.get_vel().norm().y);
      triangle.setRotation(targetAngle + 90);

      window.draw(triangle);
    }

    pf::movimento(stormo, 0.001);
    pf::comportamento_bordi(stormo);
    pf::applicazione_regole(stormo, d, ds, s, a, c);
    pf::controllo_velocità(stormo, 2);

    window.display();
  }
}

// std::cout << '\n';
// for (pf::Boid& b : stormo) {
//   std::cout << b.pos().x << ' ' << b.pos().y << '\n';
// }
// std::cout << '\n';

void simulazione_piano_due_stormi(int n1, int n2, double d, double ds, double s,
                                  double a, double c, double ds2, double s2)
{
  sf::RenderWindow window(
      sf::VideoMode(1000, 600),
      "Simulazione del comportamento di uno stormo, di Nisi, Rosini, Seren");
  constexpr int frame_rate{60};
  window.setFramerateLimit(frame_rate);

  std::vector<pf::Boid> stormo1 = pf::genera_stormo(n1);
  std::vector<pf::Boid> stormo2 = pf::genera_stormo(n2);

  float scaleFactorX = 1000.0f / 1.0f;
  float scaleFactorY = 600.0f / 1.0f;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color::Cyan);

    for (pf::Boid const& boid : stormo1) {
      sf::Vector2f pixelPos = realeToPixel(boid.get_pos().x, boid.get_pos().y,
                                           scaleFactorX, scaleFactorY);
      sf::CircleShape shape(3);
      shape.setPointCount(3);
      shape.setPosition(pixelPos);
      shape.setFillColor(sf::Color::Black);
      window.draw(shape);
    }
    pf::movimento(stormo1, 0.001);
    pf::comportamento_bordi(stormo1);
    pf::applicazione_regole_due_stormi(stormo1, stormo2, d, ds, s, a, c, ds2,
                                       s2);
    pf::controllo_velocità(stormo1, 2);

    for (pf::Boid const& boid : stormo2) {
      sf::Vector2f pixelPos = realeToPixel(boid.get_pos().x, boid.get_pos().y,
                                           scaleFactorX, scaleFactorY);
      sf::CircleShape shape(3);
      shape.setPointCount(3);
      shape.setPosition(pixelPos);
      shape.setFillColor(sf::Color::Red);
      window.draw(shape);
    }
    pf::movimento(stormo2, 0.001);
    pf::comportamento_bordi(stormo2);
    pf::applicazione_regole_due_stormi(stormo2, stormo1, d, ds, s, a, c, ds2,
                                       s2);
    pf::controllo_velocità(stormo2, 2);

    window.display();
  }
}

void grafici(int n, double d, double ds, double s, double a, double c)
{}

int main()
{
  std::cout << "\n    ---------------------------------------------\n";
  std::cout << "    |SIMULAZIONE DEL COMPORTAMENTO DI UNO STORMO|\n";
  std::cout << "    ---------------------------------------------\n";
  std::cout << "      di Riccardo Nisi, Emanuele Rosini, Federico Seren\n\n";
  std::cout << "Opzioni:\n"
            << "a. Visualizzare sul piano il comportamento di uno stormo\n";
  std::cout << "b. Visualizzare sul piano il comportamento di uno stormo "
               "usando i parametri consigliati\n";
  std::cout << "c. Visualizzare l'andamento di velocità, posizione e distanza "
               "medie in funzione del tempo con dei grafici\n";
  std::cout << "d. Visualizzare sul piano il comportamento di due stormi (di "
               "specie diverse)\n";
  std::cout << "e. Visualizzare sul piano il comportamento di due stormi "
               "usando i parametri consigliati\n";
  char op;
  std::cin >> op;
  switch (op) {
  case 'a':
    std::cout << "Inserire il numero di uccelli: ";
    int n;
    std::cin >> n;
    assert(n > 1);
    std::cout << "Inserire d, ds, s, a, c: ";
    double d;
    double ds;
    double s;
    double a;
    double c;
    std::cin >> d >> ds >> s >> a >> c;
    assert(d >= 0 && d <= std::sqrt(2));
    assert(ds >= 0 && ds <= std::sqrt(2));
    assert(s > 0);
    assert(a > 0);
    assert(c > 0);
    simulazione_piano(n, d, ds, s, a, c);
    break;
  case 'b':
    simulazione_piano(50, 0.02, 0.005, 0.05, 0.15, 0.05);
    break;
  case 'c':
    std::cout << "Inserire il numero di uccelli: ";
    std::cin >> n;
    assert(n > 1);
    std::cout << "Inserire d, ds, s, a, c: ";
    std::cin >> d >> ds >> s >> a >> c;
    assert(d >= 0 && d <= std::sqrt(2));
    assert(ds >= 0 && ds <= std::sqrt(2));
    assert(s > 0);
    assert(a > 0);
    assert(c > 0);
    grafici(n, d, ds, s, a, c);
    break;
  case 'd':
    std::cout
        << "Inserire il numero di uccelli che compongono il primo stormo: ";
    std::cin >> n;
    assert(n > 1);
    std::cout
        << "Inserire il numero di uccelli che compongono il secondo stormo: ";
    int n2;
    std::cin >> n2;
    assert(n2 > 1);
    std::cout << "Inserire d, ds, s, a, c, che si applicano tra gli uccelli di "
                 "una stessa specie: ";
    std::cin >> d >> ds >> s >> a >> c;
    assert(d >= 0 && d <= std::sqrt(2));
    assert(ds >= 0 && ds <= std::sqrt(2));
    assert(s > 0);
    assert(a > 0);
    assert(c > 0);
    std::cout << "Inserire ds2 , s2, che si applicano tra specie diverse: ";
    double ds2;
    double s2;
    std::cin >> ds2 >> s2;
    assert(s2 > 0);
    assert(ds2 >= 0 && ds2 <= std::sqrt(2));
    simulazione_piano_due_stormi(n, n2, d, ds, s, a, c, ds2, s2);
    break;
  case 'e':
    simulazione_piano_due_stormi(100, 100, 0.03, 0.0025, 0.75, 0.5, 0.5, 0.02,
                                 0.95);
    break;
  default:
    std::cout << "Carattere non valido";
    break;
  }
  std::cout << '\n' << '\n';
}