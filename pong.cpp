#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    srand((unsigned)time(NULL));
    bool goUp = false, goDown = false;
    float velX = (rand() % 2) ? -1.4 : 1.4;
    float velY = (rand() % 2) ? -1.4 : 1.4;
    int leftScore = 0, rightScore = 0;
    float rightSpeed = 1.2;

    sf::RenderWindow window(sf::VideoMode(200, 200), "Pong!");
    window.setFramerateLimit(60);
    sf::RectangleShape left(sf::Vector2f(10, 40));
    left.setPosition(0, 80);
    sf::RectangleShape right(sf::Vector2f(10, 40));
    right.setPosition(190, 80);
    sf::CircleShape ball(6);
    ball.setPosition(96, 96);

    sf::Font font;
    if (!font.loadFromFile("Square.ttf"))
        std::cout << "Error loading font; won't display scores." << std::endl;
    sf::Text txtLeftScore;
    txtLeftScore.setFont(font);
    txtLeftScore.setString("0");
    txtLeftScore.setPosition(80, 0);
    txtLeftScore.setOrigin(txtLeftScore.getLocalBounds().width, 0);
    sf::Text txtRightScore;
    txtRightScore.setFont(font);
    txtRightScore.setString("0");
    txtRightScore.setPosition(120, 0);

    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();
                    break;
                }

                case sf::Event::KeyPressed:
                {
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Up:
                            goUp = true;
                            break;

                        case sf::Keyboard::Down:
                            goDown = true;
                            break;

                        default:
                            break;
                    }
                    break;
                }

                case sf::Event::KeyReleased:
                {
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Up:
                            goUp = false;
                            break;

                        case sf::Keyboard::Down:
                            goDown = false;
                            break;

                        default:
                            break;
                    }
                }

                default:
                {
                    break;
                }
            }
        }

        if (goUp && left.getPosition().y > 0)
            left.move(0, -3);
        else if (goDown && left.getPosition().y < 160)
            left.move(0, 3);

        ball.move(velX, velY);
        
        // Bounce off the top/bottom
        if (ball.getPosition().y < 0 || ball.getPosition().y > 188)
        {
            velY = -velY;
            ball.move(velX, velY);
        }

        // Check if the ball collided with one of the paddles.
        // If so, invert the x velocity and increase speed a bit.
        if (ball.getGlobalBounds().intersects(left.getGlobalBounds()))
        {
            velX = -velX * 1.05;
            velY *= 1.05;
        }
        else if (ball.getGlobalBounds().intersects(right.getGlobalBounds()))
        {
            velX = -velX * 1.05;
            velY *= 1.05;
        }

        // Check for scores
        if (ball.getPosition().x < 7)
        {
            rightScore++;
            txtRightScore.setString(std::to_string(rightScore));

            ball.setPosition(96, 96);
            velX = 1.4;
            velY = velY > 0 ? 1.4 : -1.4;
        }
        else if (ball.getPosition().x > 182)
        {
            leftScore++;
            txtLeftScore.setString(std::to_string(leftScore));
            txtLeftScore.setOrigin(txtLeftScore.getLocalBounds().width, 0);

            ball.setPosition(96, 96);
            velX = -1.4;
            velY = velY > 0 ? 1.4 : -1.4;
        }

        // Move the right paddle
        if (ball.getPosition().y > right.getPosition().y)
            right.move(0, rightSpeed);
        else if (ball.getPosition().y < right.getPosition().y)
            right.move(0, -rightSpeed);


        window.clear();

        window.draw(left);
        window.draw(right);
        window.draw(ball);
        window.draw(txtLeftScore);
        window.draw(txtRightScore);

        window.display();
    }

    return 0;
}
