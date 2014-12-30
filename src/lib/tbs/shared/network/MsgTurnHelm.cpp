#include <shared/network/MsgTurnHelm.h>

MsgTurnHelm::MsgTurnHelm(MsgOrientation orientation)
: MsgData() {
    (*this) << static_cast<sf::Int8> (orientation);
}

MsgTurnHelm::~MsgTurnHelm() {

}
