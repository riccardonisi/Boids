#include "simulation.hpp"
#include <memory>
#include <string>

namespace pf {

void simulation_one_flock(double n, float d, float ds, float s, float a, float c,
                       float field_of_view)
{
  constexpr int pixelx = 1000;
  constexpr int pixely = 600;
  sf::RenderWindow window(
      sf::VideoMode(pixelx, pixely),
      "simulation_one_flock of one flock's behavior, by Nisi, Rosini, Seren");
  window.setPosition(sf::Vector2i(50, 70));
  constexpr int frame_rate{60};
  window.setFramerateLimit(frame_rate);

  // Vettore di boids, ossia lo flock
  std::vector<Boid> flock = generate_flock(n);

  // Fattori di scala per la conversione
  float scale_factor_x = static_cast<float>(pixelx) / 1.0f;
  float scale_factor_y = static_cast<float>(pixely) / 1.0f;

  // Crea una texture (e poi una sprite) con lo sfondo
  sf::Texture texture;
  if (!texture.loadFromFile("sfondo.png")) {
    throw std::runtime_error{"Cannot load background image"};
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

    window.clear(sf::Color(0, 160, 200, 200));
    window.draw(sprite);

    // Disegnare i punti convertiti in pixel
    for (Boid const& boid : flock) {
      sf::Vector2f pixelPos = real_to_pixel(boid.get_pos().x, boid.get_pos().y,
                                           scale_factor_x, scale_factor_y);
      sf::ConvexShape triangle;
      triangle.setPointCount(3);
      triangle.setPoint(0, sf::Vector2f(0, -3.3f)); // Vertice superiore (punta)
      triangle.setPoint(
          1, sf::Vector2f(-2.0f, 3.3f)); // Punto a sinistra della base
      triangle.setPoint(2,
                        sf::Vector2f(2.0f, 3.3f)); // Punto a destra della base
      triangle.setPosition(pixelPos);
      triangle.setFillColor(sf::Color::Black);
      triangle.setOrigin(0, -3.3f);

      float targetAngle = calculate_rotation_angle(
          boid.get_vel().x, boid.get_vel().y);
      triangle.setRotation(targetAngle + 90);

      window.draw(triangle);
    }

    movement(flock, 0.001f);
    boundary_behavior(flock);
    flocking_behavior(flock, d, ds, s, a, c, field_of_view);
    random_boost(flock, 0.01f, 0.01f);
    speed_control(flock, 2);

    window.display();
  }
}

void simulation_two_flocks(double n1, double n2, float d, float ds, float s,
                                  float a, float c, float ds2, float s2,
                                  float field_of_view)
{
  constexpr int pixelx = 1000;
  constexpr int pixely = 600;
  sf::RenderWindow window(
      sf::VideoMode(pixelx, pixely),
      "simulation_two_flocks of two flocks' behavior, by Nisi, Rosini, Seren");
  window.setPosition(sf::Vector2i(50, 70));
  constexpr int frame_rate{60};
  window.setFramerateLimit(frame_rate);

  std::vector<Boid> flock1 = generate_flock(n1);
  std::vector<Boid> flock2 = generate_flock(n2);

  float scale_factor_x = static_cast<float>(pixelx) / 1.0f;
  float scale_factor_y = static_cast<float>(pixely) / 1.0f;

  sf::Texture texture;
  if (!texture.loadFromFile("sfondo.png")) {
    throw std::runtime_error{"Cannot load backgroung image"};
  }
  sf::Sprite sprite;
  sprite.setTexture(texture);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color(0, 160, 200, 200));
    window.draw(sprite);

    for (Boid const& boid : flock1) {
      sf::Vector2f pixelPos = real_to_pixel(boid.get_pos().x, boid.get_pos().y,
                                           scale_factor_x, scale_factor_y);
      sf::ConvexShape triangle;
      triangle.setPointCount(3);
      triangle.setPoint(0, sf::Vector2f(0, -3.3f));
      triangle.setPoint(1, sf::Vector2f(-2.0f, 3.3f));
      triangle.setPoint(2, sf::Vector2f(2.0f, 3.3f));
      triangle.setPosition(pixelPos);
      triangle.setFillColor(sf::Color::Black);
      triangle.setOrigin(0, -3.3f);
      float targetAngle = calculate_rotation_angle(
          normalization(boid.get_vel()).x, normalization(boid.get_vel()).y);
      triangle.setRotation(targetAngle + 90);
      window.draw(triangle);
    }
    movement(flock1, 0.001f);
    boundary_behavior(flock1);
    flocking_behavior_two_flocks(flock1, flock2, d, ds, s, a, c, ds2, s2,
                                   field_of_view);
    random_boost(flock1, 0.01f, 0.01f);
    speed_control(flock1, 2.0);

    for (Boid const& boid : flock2) {
      sf::Vector2f pixelPos = real_to_pixel(boid.get_pos().x, boid.get_pos().y,
                                           scale_factor_x, scale_factor_y);
      sf::ConvexShape triangle;
      triangle.setPointCount(3);
      triangle.setPoint(0, sf::Vector2f(0, -3.3f));
      triangle.setPoint(1, sf::Vector2f(-2.0f, 3.3f));
      triangle.setPoint(2, sf::Vector2f(2.0f, 3.3f));
      triangle.setPosition(pixelPos);
      triangle.setFillColor(sf::Color::Red);
      triangle.setOrigin(0, -3.3f);
      float targetAngle = calculate_rotation_angle(
          normalization(boid.get_vel()).x, normalization(boid.get_vel()).y);
      triangle.setRotation(targetAngle + 90);
      window.draw(triangle);
    }
    movement(flock2, 0.001f);
    boundary_behavior(flock2);
    flocking_behavior_two_flocks(flock2, flock1, d, ds, s, a, c, ds2, s2,
                                   field_of_view);
    random_boost(flock2, 0.01f, 0.01f);
    speed_control(flock2, 2.0f);

    window.display();
  }
}

void graphs(double n, float d, float ds, float s, float a, float c, float field_of_view)
{
  constexpr int pixelx = 1200;
  constexpr int pixely = 650;
  sf::RenderWindow window(
      sf::VideoMode(pixelx, pixely),
      "simulation_one_flock of one flock's behavior, by Nisi, Rosini, Seren");
  window.setPosition(sf::Vector2i(10, 40));
  constexpr int frame_rate{120};
  window.setFramerateLimit(frame_rate);

  std::vector<Boid> flock = generate_flock(n);

  float scale_factor_x = 300.0f / 1.0f;
  float scale_factor_y = 250.0f / 1.0f;

  std::vector<float> meanpos;
  meanpos.push_back(mean_position(flock));
  std::vector<float> meanvel;
  meanvel.push_back(mean_velocity(flock));
  std::vector<float> meandist;
  meandist.push_back(mean_distance(flock));
  std::vector<float> devpos;
  devpos.push_back(standdev_position(flock));
  std::vector<float> devvel;
  devvel.push_back(standdev_velocity(flock));
  std::vector<float> devdist;
  devdist.push_back(standdev_distance(flock));

  sf::Texture sfondo_texture;
  if (!sfondo_texture.loadFromFile("sfondo_graphs.png")) {
    throw std::runtime_error{"Cannot load background image"};
  }
  sf::Sprite sfondo_sprite;
  sfondo_sprite.setTexture(sfondo_texture);

  sf::RenderTexture renderTexture;
  if (!renderTexture.create(300, 250)) {
    throw std::runtime_error{
        "Cannot render graphs' textures"};
  }
  sf::RenderTexture renderTextureTime;
  if (!renderTextureTime.create(355, 15)) {
    throw std::runtime_error{
        "Cannot render time's texture"};
  }

  sf::Clock clock;
  sf::Font font;
  if (!font.loadFromFile("cambria.ttc")) {
    throw std::runtime_error{"Cannot load font"};
  }

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    window.clear(sf::Color::White);
    window.draw(sfondo_sprite);

    renderTexture.clear(sf::Color(230, 190, 80));
    float max_y = 1.0F;
    for (int i{0}, size = static_cast<int>(meanpos.size()); i != size; ++i) {
      sf::Vector2f pixelPos =
          set_graph_point(i, meanpos[static_cast<long unsigned int>(i)], size,
                          scale_factor_x, scale_factor_y, max_y);
      sf::CircleShape shape(2);
      shape.setPosition(pixelPos);
      shape.setFillColor(sf::Color::Black);
      renderTexture.draw(shape);
    }
    renderTexture.display();
    const sf::Texture& texture1 = renderTexture.getTexture();
    sf::Sprite sprite1(texture1);
    sprite1.setPosition(51.f, 40.f);
    window.draw(sprite1);

    renderTexture.clear(sf::Color(230, 190, 80));
    max_y = 1.0F;
    for (int i{0}, size = static_cast<int>(meanvel.size()); i != size; ++i) {
      sf::Vector2f pixelPos =
          set_graph_point(i, meanvel[static_cast<long unsigned int>(i)], size,
                          scale_factor_x, scale_factor_y, max_y);
      sf::CircleShape shape(2);
      shape.setPosition(pixelPos);
      shape.setFillColor(sf::Color::Black);
      renderTexture.draw(shape);
    }
    renderTexture.display();
    const sf::Texture& texture2 = renderTexture.getTexture();
    sf::Sprite sprite2(texture2);
    sprite2.setPosition(451.f, 40.f);
    window.draw(sprite2);

    renderTexture.clear(sf::Color(230, 190, 80));
    max_y = 0.85F;
    for (int i{0}, size = static_cast<int>(meandist.size()); i != size; ++i) {
      sf::Vector2f pixelPos =
          set_graph_point(i, meandist[static_cast<long unsigned int>(i)], size,
                          scale_factor_x, scale_factor_y, max_y);
      sf::CircleShape shape(2);
      shape.setPosition(pixelPos);
      shape.setFillColor(sf::Color::Black);
      renderTexture.draw(shape);
    }
    renderTexture.display();
    const sf::Texture& texture3 = renderTexture.getTexture();
    sf::Sprite sprite3(texture3);
    sprite3.setPosition(851.f, 40.f);
    window.draw(sprite3);

    renderTexture.clear(sf::Color(230, 190, 80));
    max_y = 0.4F;
    for (int i{0}, size = static_cast<int>(devpos.size()); i != size; ++i) {
      sf::Vector2f pixelPos =
          set_graph_point(i, devpos[static_cast<long unsigned int>(i)], size,
                          scale_factor_x, scale_factor_y, max_y);
      sf::CircleShape shape(2);
      shape.setPosition(pixelPos);
      shape.setFillColor(sf::Color::Black);
      renderTexture.draw(shape);
    }
    renderTexture.display();
    const sf::Texture& texture4 = renderTexture.getTexture();
    sf::Sprite sprite4(texture4);
    sprite4.setPosition(51.f, 365.f);
    window.draw(sprite4);

    renderTexture.clear(sf::Color(230, 190, 80));
    max_y = 0.4F;
    for (int i{0}, size = static_cast<int>(devvel.size()); i != size; ++i) {
      sf::Vector2f pixelPos =
          set_graph_point(i, devvel[static_cast<long unsigned int>(i)], size,
                          scale_factor_x, scale_factor_y, max_y);
      sf::CircleShape shape(2);
      shape.setPosition(pixelPos);
      shape.setFillColor(sf::Color::Black);
      renderTexture.draw(shape);
    }
    renderTexture.display();
    const sf::Texture& texture5 = renderTexture.getTexture();
    sf::Sprite sprite5(texture5);
    sprite5.setPosition(451.f, 365.f);
    window.draw(sprite5);

    renderTexture.clear(sf::Color(230, 190, 80));
    max_y = 0.4F;
    for (int i{0}, size = static_cast<int>(devdist.size()); i != size; ++i) {
      sf::Vector2f pixelPos =
          set_graph_point(i, devdist[static_cast<long unsigned int>(i)], size,
                          scale_factor_x, scale_factor_y, max_y);
      sf::CircleShape shape(2);
      shape.setPosition(pixelPos);
      shape.setFillColor(sf::Color::Black);
      renderTexture.draw(shape);
    }
    renderTexture.display();
    const sf::Texture& texture6 = renderTexture.getTexture();
    sf::Sprite sprite6(texture6);
    sprite6.setPosition(851.f, 365.f);
    window.draw(sprite6);

    renderTextureTime.clear(sf::Color::White);
    sf::Time actual_time = clock.getElapsedTime();
    float sec     = actual_time.asSeconds();
    std::string time{std::to_string(sec)};
    std::string approx_time{time.substr(0, 3)};
    sf::Text text;
    text.setFont(font);
    text.setString(approx_time);
    text.setCharacterSize(10);
    text.setFillColor(sf::Color::Black);
    text.setPosition(288.F, 2.F);
    renderTextureTime.draw(text);
    time              = std::to_string(sec / 2.f);
    approx_time = time.substr(0, 3);
    text.setString(approx_time);
    text.setPosition(138.F, 2.F);
    renderTextureTime.draw(text);
    time              = std::to_string(sec / 4.f);
    approx_time = time.substr(0, 3);
    text.setString(approx_time);
    text.setPosition(63.F, 2.F);
    renderTextureTime.draw(text);
    time              = std::to_string(sec * 3.F / 4.f);
    approx_time = time.substr(0, 3);
    text.setString(approx_time);
    text.setPosition(213.F, 2.F);
    renderTextureTime.draw(text);
    renderTextureTime.display();
    text.setString("time (s)");
    text.setPosition(307.F, 2.F);
    renderTextureTime.draw(text);
    renderTextureTime.display();
    const sf::Texture& texture_time = renderTextureTime.getTexture();
    sf::Sprite sprite_time(texture_time);
    sprite_time.setPosition(50.f, 296.f);
    window.draw(sprite_time);
    sprite_time.setPosition(450.f, 296.f);
    window.draw(sprite_time);
    sprite_time.setPosition(850.f, 296.f);
    window.draw(sprite_time);
    sprite_time.setPosition(50.f, 621.f);
    window.draw(sprite_time);
    sprite_time.setPosition(450.f, 621.f);
    window.draw(sprite_time);
    sprite_time.setPosition(850.f, 621.f);
    window.draw(sprite_time);

    movement(flock, 0.001f);
    boundary_behavior(flock);
    flocking_behavior(flock, d, ds, s, a, c, field_of_view);
    speed_control(flock, 2.0f);

    meanpos.push_back(mean_position(flock));
    meanvel.push_back(mean_velocity(flock));
    meandist.push_back(mean_distance(flock));
    devpos.push_back(standdev_position(flock));
    devvel.push_back(standdev_velocity(flock));
    devdist.push_back(standdev_distance(flock));

    window.display();
  }
}
} // namespace pf