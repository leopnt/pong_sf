#include "ball.hpp"

Ball::Ball()
{
    m_velocity = sf::Vector2f(0.f, 0.f);
    m_shape.setRadius(10);
    m_shape.setOrigin(sf::Vector2f(5, 5));
    m_shape.setPosition(getPosition());
    m_collisionShape = sf::RectangleShape(sf::Vector2f(10*2, 10*2));
    m_collisionShape.setOrigin(sf::Vector2f(10, 10));
    m_collisionShape.setFillColor(sf::Color::Red);
}

Ball::Ball(
    int const& radius,
    sf::Vector2f const& initialPos,
    sf::Vector2f const& initialVel
)
{
    setPosition(initialPos);
    m_velocity = initialVel;
    m_shape.setRadius(radius);
    m_shape.setOrigin(sf::Vector2f(radius, radius)); //center shape on object
    m_shape.setPosition(initialPos);
    m_collisionShape = sf::RectangleShape(sf::Vector2f(radius*2, radius*2));
    m_collisionShape.setOrigin(sf::Vector2f(radius, radius));
    m_collisionShape.setFillColor(sf::Color::Red);
}

Ball::~Ball()
{
    
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // draw is virtual here to allow call: window.draw(ball) from main

    target.draw(m_shape, states);
    
    // uncomment to see the collision shape:
    //target.draw(m_collisionShape, states);
}

void Ball::process(float const& delta)
{
    // multiplying by delta makes the movement framerate-independant
    //m_position += m_velocity * delta;
    
    move(delta * m_velocity);

    // udpate shapes positions
    m_shape.setPosition(getPosition());
    m_collisionShape.setPosition(getPosition());
}

bool Ball::isCollidingWith(Block const& collider)
{
    // check collision between two rectangles

    sf::FloatRect collisionShapeBounds = m_collisionShape.getGlobalBounds();
    
    sf::RectangleShape colliderShape = collider.getCollisionShape();
    sf::FloatRect colliderShapeBounds = colliderShape.getGlobalBounds();

    if (collisionShapeBounds.intersects(colliderShapeBounds))
        return true;

    return false;
}

void Ball::collideWith(Block const& collider, int const& colliderSide)
{
    // vDrift gives the force applied by the player
    // the more the ball is centered on the block,
    // the less it will bounce
    float vDrift = getPosition().y - collider.getPosition().y;

    // map vDrift:
    float colliderHeight = collider.getCollisionShape().getSize().y;
    float ballHeight = m_collisionShape.getSize().y;
    vDrift /= (colliderHeight + ballHeight);
    if (colliderSide == 0) // left block collision
    {
        // giving side specific cases instead of flipping velocity
        // prevents the ball from being stuck inside a shape

        setVelocity(sf::Vector2f(
            // always give minimum speed (*0.6) and
            // ensure stability with maximum speed 320.f
            (abs(vDrift) + 0.6) * 320.f,
            // same as above but take into account vDrift sign
            (vDrift >= 0) ? (vDrift + 0.6) * 320.f : (vDrift - 0.6) * 320.f
            ));
    }
    if (colliderSide == 1) // right block collision
    {
        setVelocity(sf::Vector2f(
            -(abs(vDrift) + 0.6) * 320.f,
            (vDrift >= 0) ? (vDrift + 0.6) * 320.f : (vDrift - 0.6) * 320.f
            ));
    }
}

int Ball::checkAndCollide(sf::Vector2u const& windowSize)
{
    // check collision with window boundaries
    bool isOutsideLow = getPosition().y >= windowSize.y - m_shape.getRadius();
    bool isOutsideUp = getPosition().y <= 0.f + m_shape.getRadius();
    
    if (isOutsideLow)
        m_velocity.y = -abs(m_velocity.y); // ensure ball is not stuck with abs
    
    if (isOutsideUp)
        m_velocity.y = abs(m_velocity.y);

    bool isOutsideRight = getPosition().x >= windowSize.x + m_shape.getRadius();
    bool isOutsideLeft = getPosition().x <= 0.f - m_shape.getRadius();
    
    // return the winner side, 0 : left, 1 : right
    if (isOutsideRight)
    {
        return 0;
    }
    else if (isOutsideLeft)
    {
        return 1;
    }

    return -1; // return -1 to indicate error
}

sf::Vector2f Ball::getVelocity() const
{
    return m_velocity;
}

void Ball::setVelocity(sf::Vector2f newVelocity)
{
    m_velocity = newVelocity;
}

void Ball::reset(sf::Vector2u const& windowSize)
{
    setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y / 2)); // center

    // get random directions
    float randx = (float) (rand() % 2);
    float randy = (float) (rand() % 2);
    
    // get random magnitudes from direction
    float vx = (randx == 0 ? 100 + rand() % 200 : -100 - rand() % 200);
    float vy = (randy == 0 ? 100 + rand() % 200 : -100 - rand() % 200);
    
    m_velocity = sf::Vector2f(vx, vy); // apply random velocity
    m_shape.setPosition(getPosition());
    m_collisionShape.setPosition(getPosition());
}

int Ball::getRadius() const
{
    return m_shape.getRadius();
}
