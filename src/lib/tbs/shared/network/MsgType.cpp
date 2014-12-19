
#include <SFML/Config.hpp>
#include "shared/network/MsgType.h"

sf::Packet& operator>>(sf::Packet& packet, MsgType& en) {
    typename std::underlying_type<MsgType>::type en_t(0);
    packet >> en_t;
    en = static_cast<MsgType> (en_t);
    return packet;
}

sf::Packet& operator<<(sf::Packet& packet, MsgType en) {
    return packet << static_cast<std::underlying_type<MsgType>::type> (en);
}

sf::Packet& operator>>(sf::Packet& packet, MsgOrientation& en) {
    typename std::underlying_type<MsgOrientation>::type en_t(0);
    packet >> en_t;
    en = static_cast<MsgOrientation> (en_t);
    return packet;
}

sf::Packet& operator<<(sf::Packet& packet, MsgOrientation en) {
    return packet << static_cast<std::underlying_type<MsgOrientation>::type> (en);
}
