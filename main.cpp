#include "boids.hpp"
#include "boids2.hpp"
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

  // Esempio di vettore di posizioni reali
  std::vector<pf::Boid> stormo = pf::genera_stormo(20);

  // Fattori di scala per la conversione
  float scaleFactorX = 1000.0f / 1.0f; // Scala l'intervallo
  float scaleFactorY = 600.0f / 1.0f;  // Scala l'intervallo

  // Eseguire il loop della finestra finché è aperta
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::Cyan);

    // Disegnare i punti convertiti in pixel
    for (unsigned long int i{0}; i != stormo.size(); ++i) {
      sf::Vector2f pixelPos = realeToPixel(stormo[i].pos().x, stormo[i].pos().y,
                                           scaleFactorX, scaleFactorY);
      sf::CircleShape shape(5);
      shape.setPointCount(3);
      shape.setPosition(pixelPos);
      shape.setFillColor(sf::Color::Black);
      window.draw(shape);
    }

    pf::movimento(stormo, 0.001);
    pf::comportamento_bordi(stormo);
    pf::applicazione_regole(stormo, 0.03, 0.01, 0.85, 0.5, 0.75);

    window.display();
  }

  return 0;
}
