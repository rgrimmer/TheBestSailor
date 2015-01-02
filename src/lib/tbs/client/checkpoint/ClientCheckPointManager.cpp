#include "client/checkpoint/ClientCheckPointManager.h"
#include <iostream>
ClientCheckPointManager::ClientCheckPointManager() 
{
}

ClientCheckPointManager::~ClientCheckPointManager() {
    for (unsigned int i = 0; i < m_checkPoints.size(); ++i) {
        delete m_checkPoints.at(i);
    }
    
    m_checkPoints.empty();
}

void ClientCheckPointManager::addCheckPoint(sf::Vector2i position) {
    m_checkPoints.push_back(new ClientCheckPoint(position));
}

ClientCheckPoint* ClientCheckPointManager::getCheckPoint(int index){
    return m_checkPoints.at(index);
}

int ClientCheckPointManager::getCheckPointCount() {
    return m_checkPoints.size();
}

