#include "client/checkpoint/ClientCheckPointManager.h"
#include <iostream>
ClientCheckPointManager::ClientCheckPointManager() 
{
}

ClientCheckPointManager::~ClientCheckPointManager() {
}

void ClientCheckPointManager::addCheckPoint(sf::Vector2i position) {
    m_checkPoints.push_back(ClientCheckPoint(position));
}

const ClientCheckPoint& ClientCheckPointManager::getCheckPoint(int index) const {
    return m_checkPoints.at(index);
}

int ClientCheckPointManager::getCheckPointCount() const {
    return m_checkPoints.size();
}

const std::vector<ClientCheckPoint>& ClientCheckPointManager::getCheckPoints() const {
    return m_checkPoints;
}
