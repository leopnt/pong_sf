#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <math.h>
#include <windows.h> // this is Windows-specific to hide console

#include "ball.hpp"
#include "block.hpp"

float getFramerate(float const& delta)
{
    return 1 / delta;
}

int main()
{
    // hide console on Windows
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

    // creating the window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode(600, 400),
        "pong_sf",
        sf::Style::Default,
        settings
        );

    // choose one setting here
    // setting both may result in bugs as indicating in the SFML doc
    //window.setFramerateLimit(30); // choose this one to control fps
    window.setVerticalSyncEnabled(true); // choose this one for no stuttering

    // add delta to allow movements to be independant of frameRate
    float delta;
    sf::Clock deltaClock = sf::Clock();
    
    // create ball object with radius, position and initial velocity
    Ball ball(5, sf::Vector2f(200.f, 200.f), sf::Vector2f(-200.f, 0.f));

    // player blocks
    Block blockLeft(
        sf::Vector2f(10.f, window.getSize().y/2),
        window.getSize().y
        );
    int leftPlayerScore = 0;
    Block blockRight(
        sf::Vector2f(
            window.getSize().x - 10.f,
            window.getSize().y/2
        ),
        window.getSize().y
        );
    int rightPlayerScore = 0;

    // middle separator bar
    sf::RectangleShape middleSeparator(sf::Vector2f(3, window.getSize().y));
    middleSeparator.setPosition(sf::Vector2f(window.getSize().x / 2, 0.f));
    middleSeparator.setFillColor(sf::Color(255, 255, 255, 50));

    // text for score display
    sf::Font font;
    if (!font.loadFromFile("font/digit.ttf"))
        return EXIT_FAILURE;
    sf::Text lPlayerText, rPlayerText; // left & right player score text
    lPlayerText.setFont(font);
    rPlayerText.setFont(font);
    lPlayerText.setString(std::to_string(leftPlayerScore));
    rPlayerText.setString(std::to_string(rightPlayerScore));
    lPlayerText.setCharacterSize(38); // in pixels, not points!
    rPlayerText.setCharacterSize(38);
    lPlayerText.setPosition(sf::Vector2f(window.getSize().x / 4, 20.f));
    rPlayerText.setPosition(sf::Vector2f(3 * window.getSize().x / 4, 20.f));

    sf::Clock clock2;
    while (window.isOpen())
    {
        // check collision with player rectangles
        if (ball.isCollidingWith(blockLeft))
            ball.collideWith(blockLeft, 0);
        if (ball.isCollidingWith(blockRight))
            ball.collideWith(blockRight, 1);

        // apply collision with window boundaries
        int winner = ball.checkAndCollide(window.getSize());
        if (winner == 1)
        {
            rightPlayerScore += 1;
            ball.reset(window.getSize());
            // udpate score text
            lPlayerText.setString(std::to_string(leftPlayerScore));
            rPlayerText.setString(std::to_string(rightPlayerScore));
        }
        if (winner == 0)
        {
            leftPlayerScore += 1;
            ball.reset(window.getSize());
            // udpate score text
            lPlayerText.setString(std::to_string(leftPlayerScore));
            rPlayerText.setString(std::to_string(rightPlayerScore));
        }
        
        // apply ball movement
        ball.process(delta);

        // apply user inputs
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            blockLeft.move(0.f, -400.f * delta, window.getSize().y);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            blockLeft.move(0.f, 400.f * delta, window.getSize().y);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            blockRight.move(0.f, -400.f * delta, window.getSize().y);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            blockRight.move(0.f, 400.f * delta, window.getSize().y);


        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0,
                    event.size.width,
                    event.size.height
                    );
                window.setView(sf::View(visibleArea));
            }
        }

        // update delta, making it dynamic to framerate
        delta = deltaClock.restart().asSeconds();

        // update window
        window.clear();
        window.draw(middleSeparator);
        window.draw(ball);
        window.draw(blockLeft);
        window.draw(blockRight);
        window.draw(lPlayerText);
        window.draw(rPlayerText);
        window.display();
    }

    return 0;
}
