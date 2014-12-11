#include <shared/network/RequestTurnSail.h>

RequestTurnSail::RequestTurnSail(reqOrientation orientation)
: m_orientation(orientation) {

}

RequestTurnSail::~RequestTurnSail() {

}

reqOrientation RequestTurnSail::getOrientation() const {
    return m_orientation;
}

reqType RequestTurnSail::getType() const {
    return reqType::REQ_ACTION_TURN_SAIL;
}

void RequestTurnSail::getDataFrom(sf::Packet& packet) {
    ORIENTATION_SF_CAST sfOrientation;
    packet >> sfOrientation;
    m_orientation = static_cast<reqOrientation> (sfOrientation);
}

void RequestTurnSail::putDataIn(sf::Packet& packet) const {
    auto sfOrientation = static_cast<ORIENTATION_SF_CAST> (m_orientation);
    packet << sfOrientation;
}
