#ifndef DEF_BALL_HPP
#define DEF_BALL_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <block.hpp>

#include <math.h>

class Ball : public sf::Drawable, public sf::Transformable
{
private:
    sf::CircleShape m_shape; 
    sf::RectangleShape m_collisionShape;
    sf::Vector2f m_velocity;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
    Ball();
    Ball(
        int const& radius,
        sf::Vector2f const& initialPos,
        sf::Vector2f const& initialVel
    );
    ~Ball();
    void process(float const& delta);
    sf::Vector2f getVelocity() const;
    int checkAndCollide(sf::Vector2u const& windowSize);
    bool isCollidingWith(Block const& collider);
    void collideWith(Block const& collider, int const& colliderSide);
    void setVelocity(sf::Vector2f newVelocity);
    void reset(sf::Vector2u const& windowSize);
    int getRadius() const;
};


#endif