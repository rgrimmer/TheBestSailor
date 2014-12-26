#include <shared/network/MsgTurnHelm.h>

MsgTurnHelm::MsgTurnHelm(MsgOrientation orientation)
: MessageData() {
    (*this) << static_cast<sf::Int8> (orientation);
}

MsgTurnHelm::~MsgTurnHelm() {

}
