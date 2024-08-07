#include "boids.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

// Funzione per convertire un valore reale in pixel
sf::Vector2f realeToPixel(float x, float y, float scaleFactorX,
                          float scaleFactorY)
{
  return sf::Vector2f(x * scaleFactorX, y * scaleFactorY);
}

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 800),
                          "Conversione Reale a Pixel su SFML");

  // Esempio di vettore di posizioni reali
  std::vector<pf::Boid> stormo = pf::genera_stormo(50);

  // Fattori di scala per la conversione
  float scaleFactorX = 800.0f / 1.0f; // Scala l'intervallo [0, 100] su [0, 800]
  float scaleFactorY = 800.0f / 1.0f; // Scala l'intervallo [0, 100] su [0, 600]

  // Eseguire il loop della finestra finché è aperta
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    window.clear(sf::Color::Black);

    // Disegnare i punti convertiti in pixel
    for (const auto& dot : stormo) {
      sf::Vector2f pixelPos =
          realeToPixel(dot.pos().x, dot.pos().y, scaleFactorX, scaleFactorY);

      sf::CircleShape shape(5); // Crea un cerchio di raggio 5
      shape.setPosition(pixelPos);
      shape.setFillColor(sf::Color::White);
      window.draw(shape);
    }

    window.display();
  }

  return 0;
}
