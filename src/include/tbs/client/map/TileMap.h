#include <SFML/Graphics.hpp>
#include "shared/Utils.h"
#include "shared/entity/map/Map.h"

class TileMap : public sf::Drawable, public sf::Transformable {
    
public:

    void load(const Map &map, bool squared);

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::VertexArray m_vertices;
};