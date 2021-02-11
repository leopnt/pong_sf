#ifndef DEF_BLOCK_HPP
#define DEF_BLOCK_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

class Block : public sf::Drawable, public sf::Transformable
{
private:
    sf::RectangleShape m_collisionShape;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
    Block(sf::Vector2f const& initialPos, float const& windowSizeY);
    ~Block();
    sf::RectangleShape getCollisionShape() const;
    virtual void move(float const& vx, float const& vy, float const& windowY);
};

#endif