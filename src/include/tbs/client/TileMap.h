#include <SFML/Graphics.hpp>

#define TILE_SIZE 5

#define NB_TILES_WIDTH 200
#define NB_TILES_HEIGHT 200

#define WATER(x) (x > 0.35) ? true : false

class TileMap : public sf::Drawable, public sf::Transformable {
    
public:

    void load(const float tiles[NB_TILES_WIDTH][NB_TILES_HEIGHT], bool squared);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};