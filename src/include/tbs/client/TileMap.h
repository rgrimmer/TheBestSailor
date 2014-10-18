#include <SFML/Graphics.hpp>

#define TILE_SIZE 200

#define NB_TILES_WIDTH 800
#define NB_TILES_HEIGHT 600

class TileMap : public sf::Drawable, public sf::Transformable {
    
public:

    void load(const float* tiles, unsigned int width, unsigned int height, bool squared);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};