#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>

class Brick
{
public:
    Brick()
    {
        m_shape = sf::RectangleShape(sf::Vector2f(10, 4));
    };

    Brick(const int x, const int y)
    {
        m_shape = sf::RectangleShape(sf::Vector2f(10, 4));
        setPosition(x, y);
    };


    void setPosition(const int x, const int y)
    {
        m_shape.setPosition(x * 11 + 1, y * 5 + 1);
    };

    void setPosition(const sf::Vector2i &position)
    {
        setPosition(position.x, position.y);
    };

    sf::Vector2f getPosition() const
    {
        sf::Vector2f pos = m_shape.getPosition();
        return sf::Vector2f((pos.x - 1) / 11, (pos.y - 1) / 5);
    };

    void setColor(const sf::Color &color)
    {
        m_shape.setFillColor(color);
        m_shape.setOutlineColor(color);
    };

    void draw(sf::RenderWindow &window)
    {
        window.draw(m_shape);
    };

private:
    sf::RectangleShape &m_shape;
}

bool leftPressed, rightPressed, upPressed, downPressed;
bool inEditor;
sf::RectangleShape cursor(sf::Vector2f(10, 4));;
std::vector<Brick> bricks;

void loadLevel(std::string name)
{
    std::ifstream ifs("breakout/" + name + ".lvl");
    bricks.clear();
    
    // If there was an error opening the level file, return an empty vector.
    if (!ifs.good())
    {
        std::cout << "Error opening level \"" << name << "\"!" << std::endl;
    }

    while (ifs.good())
    {
        try
        {
            // Read an x and y coordinate
            int x, y;
            ifs >> x >> y;

            // Read the color
            sf::Color color;
            ifs >> color;

            // Print it for debugging reasons
            std::cout << "Brick found at (" << x << ", " << y << ")" << std::endl;

            sf::RectangleShape brick(sf::Vector2f(10, 4));
            brick.setPosition(x, y);
            bricks.push_back(brick);
        }
        catch (...)
        {
            std::cout << "Error loading level \"" << name << "\"!" << std::endl;
            return bricks;
        }
    }
    return bricks;
}

void handleEvents(sf::RenderWindow &window)
{
    sf::Event event;
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
                    case sf::Keyboard::Left:
                    case sf::Keyboard::A:
                    {
                        leftPressed = true;
                        break;
                    }

                    case sf::Keyboard::Right:
                    case sf::Keyboard::D:
                    {
                        rightPressed = true;
                        break;
                    }

                    case sf::Keyboard::Up:
                    case sf::Keyboard::W:
                    {
                        upPressed = true;
                        break;
                    }

                    case sf::Keyboard::Down:
                    case sf::Keyboard::S:
                    {
                        downPressed = true;
                        break;
                    }

                    case sf::Keyboard::E:
                    {
                        inEditor = !inEditor;
                        break;
                    }

                    default:
                    {
                        break;
                    }
                }

            }

            case sf::Event::KeyReleased:
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Left:
                    case sf::Keyboard::A:
                    {
                        leftPressed = false;
                        break;
                    }

                    case sf::Keyboard::Right:
                    case sf::Keyboard::D:
                    {
                        rightPressed = false;
                        break;
                    }

                    case sf::Keyboard::Up:
                    case sf::Keyboard::W:
                    {
                        upPressed = false;
                        break;
                    }

                    case sf::Keyboard::Down:
                    case sf::Keyboard::S:
                    {
                        downPressed = false;
                        break;
                    }

                    default:
                    {
                        break;
                    }
                }
            }

            default:
            {
                break;
            }
        }
    }
}

void update()
{
    if (inEditor)
    {
        if (leftPressed)
        {
            leftPressed = false;
            cursorX--;
            if (cursorX < 0)
                cursorX = 0;
        }
        else if (rightPressed)
        {
            rightPressed = false;
            cursorX++;
            if (cursorX > 17)
                cursorX = 17;
        }
        else if (upPressed)
        {
            upPressed = false;
            cursorY--;
            if (cursorY < 0)
                cursorY = 0;
        }
        else if (downPressed)
        {
            downPressed = false;
            cursorY++;
            if (cursorY > 7)
                cursorY = 7;
        }
        
        if (spacePressed)
        {


        cursor.setPosition(cursorX * 11 + 1, cursorY * 5 + 1);
    }
    else
    {
        if (leftPressed)
        {
            if (--paddleX 
}

void render(sf::RenderWindow &window)
{
    window.clear();

    if (inEditor)
        window.draw(cursor);

    window.display();
}

int main()
{

    sf::RenderWindow window(sf::VideoMode(200, 200), "BreakOut!");
    window.setFramerateLimit(60);
    std::vector<sf::RectangleShape> bricks;

    while (window.isOpen())
    {
        handleEvents(window);
        update();
        render(window);
    }
}
