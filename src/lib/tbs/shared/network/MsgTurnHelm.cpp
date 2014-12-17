#include <shared/network/MsgTurnHelm.h>

MsgTurnHelm::MsgTurnHelm(msgOrientation orientation)
: m_orientation(orientation) {

}

MsgTurnHelm::~MsgTurnHelm() {

}

msgOrientation MsgTurnHelm::getOrientation() const {
    return m_orientation;
}

MsgType MsgTurnHelm::getType() const {
    return MsgType::MSG_ACTION_TURN_HELM;
}

void MsgTurnHelm::getDataFrom(sf::Packet& packet) {
    ORIENTATION_SF_CAST sfOrientation;
    packet >> sfOrientation;
    m_orientation = static_cast<msgOrientation>(sfOrientation);
}

void MsgTurnHelm::putDataIn(sf::Packet& packet) const {
    auto sfOrientation = static_cast<ORIENTATION_SF_CAST>(m_orientation);
    packet << sfOrientation;
}