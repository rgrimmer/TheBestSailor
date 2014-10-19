/* 
 * File:   EmplifiedSocket.h
 * Author: maxence
 *
 * Created on 13 octobre 2014, 21:34
 */

#ifndef EMPLIFIEDSOCKET_H
#define	EMPLIFIEDSOCKET_H

#include <SFML/Network/UdpSocket.hpp>
#include <SFML/Network/IpAddress.hpp>

class EmplifiedSocket : public sf::UdpSocket {
public:
    EmplifiedSocket();
    EmplifiedSocket(const sf::IpAddress &adress, unsigned short port);
    EmplifiedSocket(const EmplifiedSocket& orig);
    virtual ~EmplifiedSocket();
    
    inline const sf::IpAddress & adress() const { return m_adress; }
    inline sf::IpAddress & adress() { return m_adress; }
    inline unsigned short& port() { return m_port; }
    inline unsigned short port() const { return m_port; }
    inline sf::UdpSocket& socket() { return *this; }
    inline const sf::UdpSocket& socket() const { return *this; }
    inline void setAdress(const sf::IpAddress & adress) { m_adress = adress; }
    inline void setPort(unsigned short port) { m_port = port; }
    
    
    
private:
    sf::IpAddress m_adress;
    unsigned short m_port;

};

#endif	/* EMPLIFIEDSOCKET_H */

