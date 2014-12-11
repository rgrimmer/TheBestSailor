#include <shared/network/RequestTurnHelm.h>

RequestTurnHelm::RequestTurnHelm(reqOrientation orientation)
: m_orientation(orientation) {

}

RequestTurnHelm::~RequestTurnHelm() {

}

reqOrientation RequestTurnHelm::getOrientation() const {
    return m_orientation;
}

reqType RequestTurnHelm::getType() const {
    return reqType::REQ_ACTION_TURN_HELM;
}

void RequestTurnHelm::getDataFrom(sf::Packet& packet) {
    ORIENTATION_SF_CAST sfOrientation;
    packet >> sfOrientation;
    m_orientation = static_cast<reqOrientation>(sfOrientation);
}

void RequestTurnHelm::putDataIn(sf::Packet& packet) const {
    auto sfOrientation = static_cast<ORIENTATION_SF_CAST>(m_orientation);
    packet << sfOrientation;
}