#include <shared/network/MsgTurnSail.h>

MsgTurnSail::MsgTurnSail(msgOrientation orientation)
: m_orientation(orientation) {

}

MsgTurnSail::~MsgTurnSail() {

}

msgOrientation MsgTurnSail::getOrientation() const {
    return m_orientation;
}

MsgType MsgTurnSail::getType() const {
    return MsgType::MSG_ACTION_TURN_SAIL;
}

void MsgTurnSail::getDataFrom(sf::Packet& packet) {
    ORIENTATION_SF_CAST sfOrientation;
    packet >> sfOrientation;
    m_orientation = static_cast<msgOrientation> (sfOrientation);
}

void MsgTurnSail::putDataIn(sf::Packet& packet) const {
    auto sfOrientation = static_cast<ORIENTATION_SF_CAST> (m_orientation);
    packet << sfOrientation;
}
