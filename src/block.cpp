#include "block.hpp"

Block::Block(sf::Vector2f const& initialPos, float const& windowSizeY)
{
    m_collisionShape = sf::RectangleShape(sf::Vector2f(5.f, 40.f));
    
    // center shape on position
    m_collisionShape.setOrigin(m_collisionShape.getSize() / 2.f);
    move(initialPos.x, initialPos.y, windowSizeY);
}

Block::~Block()
{
}

void Block::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_collisionShape, states);
}

sf::RectangleShape Block::getCollisionShape() const
{
    return m_collisionShape;
}

void Block::move(float const& vx, float const& vy, float const& windowY)
{
    int blockHeight = m_collisionShape.getSize().y / 2;
    bool isAboveLow = (getPosition().y + vy) > windowY - blockHeight;
    bool isAboveUp = (getPosition().y + vy) < blockHeight;

    // keep the block inside the window;
    if (!isAboveUp && !isAboveLow)
    {
        sf::Transformable::move(vx, vy); // move object
        m_collisionShape.setPosition(getPosition()); // make shape follow object
    }
}
