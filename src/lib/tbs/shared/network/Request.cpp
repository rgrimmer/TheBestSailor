#include <shared/network/Request.h>

Request::Request(reqType type, unsigned int id) : m_type(type), m_id(id){  

}

Request::~Request() {

}

sf::Packet Request::createPacket() {
    sf::Packet packet;
    
    sf::Uint8 typeUi8 = static_cast<sf::Uint8>(m_type);
    sf::Uint8 idUi8 = static_cast<sf::Uint8>(m_id);
    
    packet << typeUi8 << idUi8;
    
    return packet;
}