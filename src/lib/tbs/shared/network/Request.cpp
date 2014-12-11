#include <shared/network/Request.h>
#define ID_SF_CAST sf::Uint8
unsigned int Request::popID(sf::Packet& packet) {
    ID_SF_CAST sfID;
    packet >> sfID;
    return static_cast<unsigned int>(sfID);
}

Request::Request(unsigned int id, const RequestData& data)
: m_id(id)
, m_data(&data) {

}

Request::~Request() {
//    delete m_data; // @TODO warning
}

sf::Packet Request::getPacket() const {
    sf::Packet packet;

    auto idUi8 = static_cast<ID_SF_CAST> (m_id);
    packet << idUi8;
    return m_data->toPacketWithType(packet);
}