#include <shared/network/RequestTurnHelm.h>

RequestTurnHelm::RequestTurnHelm(reqType type, unsigned int id) : Request(type, id) {

}

RequestTurnHelm::~RequestTurnHelm() {

}

sf::Packet RequestTurnHelm::createPacket() {
    sf::Packet packet = Request::createPacket();
    return packet;
}