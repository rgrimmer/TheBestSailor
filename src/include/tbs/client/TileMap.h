#include <SFML/Graphics.hpp>
#include "shared/Utils.h"

class TileMap : public sf::Drawable, public sf::Transformable {
    
public:

    void load(const float tiles[NB_TILES_WIDTH][NB_TILES_HEIGHT], bool squared);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};