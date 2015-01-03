/* 
 * File:   ClientCheckPointManager.h
 * Author: remy
 *
 * Created on 2 janvier 2015, 21:59
 */

#ifndef CLIENTCHECKPOINTMANAGER_H
#define	CLIENTCHECKPOINTMANAGER_H

#include <vector>
#include "client/checkpoint/ClientCheckPoint.h"

class ClientCheckPointManager {
public:
    explicit ClientCheckPointManager();
    virtual ~ClientCheckPointManager();

    void addCheckPoint(sf::Vector2i position);

    int getCheckPointCount() const;
    const ClientCheckPoint& getCheckPoint(int index) const;
    const std::vector<ClientCheckPoint>& getCheckPoints() const;

private:
    std::vector<ClientCheckPoint> m_checkPoints;
};

#endif	/* CLIENTCHECKPOINTMANAGER_H */