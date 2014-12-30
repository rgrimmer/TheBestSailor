#include "shared/network/MsgTurnSail.h"

MsgTurnSail::MsgTurnSail(MsgOrientation orientation)
: MsgData() {
    (*this) << static_cast<sf::Int8> (orientation);
}

MsgTurnSail::~MsgTurnSail() {

}