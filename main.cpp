#include<SFML/Graphics.hpp>
#include<string>

void changeCounter(sf::Text& counter, int count)
{
  counter.setString(std::to_string(std::stoi(std::string(counter.getString())) + count));
}
void setPosition(sf::CircleShape& ball, sf::Vector2f& defaultPosition, sf::RenderWindow& window)
{
  //ball.setPosition(sf::Vector2f(0.f, defaultPosition.y));
  ball.setPosition(sf::Vector2f(sf::Mouse::getPosition(window).x - ball.getRadius(), defaultPosition.y));
}
int main()
{
  sf::RenderWindow window(sf::VideoMode(500, 500), "Sfml app");
  window.setFramerateLimit(60);

  //TEXT&FONT
  sf::Text counter;
  sf::Font font;
  font.loadFromFile("font.ttf");
  counter.setFont(font);
  counter.setString("0");
  counter.setCharacterSize(24);
  counter.setFillColor(sf::Color::Black);

  //VARIABLES
  bool isMovingRight = true;
  bool isShot = false;
 
  //SHAPES
  sf::CircleShape hoop(20.f);
  hoop.setFillColor(sf::Color::Black);
  hoop.setOutlineThickness(2.f);
  hoop.setOutlineColor(sf::Color::Blue);

  sf::CircleShape ball(10.f);
  sf::Vector2f defaultPosition(0.f, window.getSize().y - 2 * ball.getRadius());
  ball.setFillColor(sf::Color::Blue);
  ball.setPosition(defaultPosition);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    //UPDATE
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      isShot = true;
    if (hoop.getPosition().x + 2 * hoop.getRadius() >= window.getSize().x)
      isMovingRight = false;
    if (hoop.getPosition().x <= 0)
      isMovingRight = true;

    if (isMovingRight)
      hoop.move(10.f, 0.f);
    else
      hoop.move(-10.f, 0.f);
    if (!isShot) 
      setPosition(ball, defaultPosition, window);
    else
    {
      if (ball.getPosition().y <= 0)
      {
        isShot = false;
        changeCounter(counter, -2);
        setPosition(ball, defaultPosition, window);
      }
      ball.move(0.f, -15.f);
    }

    if (ball.getGlobalBounds().intersects(hoop.getGlobalBounds()))
    {
      changeCounter(counter, 1);
      isShot = false;
      setPosition(ball, defaultPosition, window);
    }

    //DRAW
    window.clear(sf::Color::White);

    window.draw(hoop);
    window.draw(ball);
    window.draw(counter);

    window.display();
  }


  return 0;
}
