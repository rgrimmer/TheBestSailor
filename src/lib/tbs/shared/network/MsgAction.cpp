#include <shared/network/MsgAction.h>

MsgAction::MsgAction(std::bitset<4> keys)
: MsgData(MsgType::Action) {
    (*this) << static_cast<sf::Uint8> (keys.to_ulong());
}

MsgAction::~MsgAction() {

}
