#include <SFML/Graphics.hpp>

class TileMap : public sf::Drawable, public sf::Transformable {
    
public:

    void load(sf::Vector2u tileSize, const float* tiles, unsigned int width, unsigned int height);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};