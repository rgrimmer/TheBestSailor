#include <client/ClientPlayer.h>

ClientPlayer::ClientPlayer(const unsigned int id, const std::string & name) : m_name(name), m_id(id){

}

ClientPlayer::~ClientPlayer() {
    
}

void ClientPlayer::setId(const unsigned int id) {
    m_id = id;
}

void ClientPlayer::setName(const std::string& name) {
    m_name = name;
}

unsigned int ClientPlayer::getId() const {
    return m_id;
}

std::string ClientPlayer::getName() const {
    return m_name;
}



