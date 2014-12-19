#include "shared/network/MsgTurnSail.h"

MsgTurnSail::MsgTurnSail(MsgOrientation orientation)
: MessageData(MsgType::ActionTurnSail) {
    (*this) << static_cast<sf::Int8> (orientation);
}

MsgTurnSail::~MsgTurnSail() {

}