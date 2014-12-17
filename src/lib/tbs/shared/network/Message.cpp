#include <shared/network/Message.h>

unsigned int Message::popID(sf::Packet& packet) {
    ID_SF_CAST sfID;
    packet >> sfID;
    return static_cast<unsigned int> (sfID);
}

Message::Message(unsigned int id, const MessageData& data)
: m_id(id)
, m_data(&data) {

}

Message::~Message() {
    //    delete m_data; // @TODO warning
}

sf::Packet Message::getPacket() const {
    sf::Packet packet;

    auto idUi8 = static_cast<ID_SF_CAST> (m_id);
    packet << idUi8;
    return m_data->toPacketWithType(packet);
}

MsgType Message::getType() const {
    return m_data->getType();
}