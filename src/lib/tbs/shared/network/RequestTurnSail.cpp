#include <shared/network/RequestTurnSail.h>

RequestTurnSail::RequestTurnSail(reqType type, unsigned int id) : Request(type, id) {

}

RequestTurnSail::~RequestTurnSail() {

}

sf::Packet RequestTurnSail::createPacket() {
    sf::Packet packet = Request::createPacket();
    return packet;
}
