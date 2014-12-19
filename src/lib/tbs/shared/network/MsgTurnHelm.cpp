#include <shared/network/MsgTurnHelm.h>

MsgTurnHelm::MsgTurnHelm(MsgOrientation orientation)
: MessageData(MsgType::ActionTurnHelm) {
    (*this) << static_cast<sf::Int8> (orientation);
}

MsgTurnHelm::~MsgTurnHelm() {

}
