/* 
 * File:   ConnectionManager.h
 * Author: maxence
 *
 * Created on 11 octobre 2014, 20:10
 */

#ifndef UDPSOCKETMANAGER_H
#define	UDPSOCKETMANAGER_H

#include <vector>
#include <tuple>

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/SocketSelector.hpp>
#include <SFML/Network/UdpSocket.hpp>


class Remote : public std::pair<sf::IpAddress, unsigned short> {
    public :
        Remote() {}
        Remote(sf::IpAddress adress, unsigned short port) {
            first = adress;
            second = port;
        }
    virtual ~Remote() {}

        
        inline const sf::IpAddress& adress() const { return first; }
        inline sf::IpAddress adress() { return first; }
        inline unsigned short port() const { return second; }
};

class RemoteList : public std::vector<Remote> {
    
};


class UdpSocketManager {
    
public:
    static const unsigned short serverPort = 1234;
    static const sf::IpAddress serverAddress;
    static const unsigned short clientPort = 1248;
    static const sf::IpAddress clientAddress;

public:
    UdpSocketManager();
    UdpSocketManager(const UdpSocketManager& orig);
    virtual ~UdpSocketManager();

    inline const RemoteList * receiver() const { 
        return  m_receiver;
    }
    inline RemoteList * receiver() { 
        return  m_receiver;
    }
    inline void setReceiver(RemoteList *receiver) {
        m_receiver = receiver;
    }

    void addRemote(const sf::IpAddress &remoteAddress, unsigned short remotePort);

    void bind(unsigned short socketPort = sf::Socket::AnyPort);
    void connectTo(const sf::IpAddress &remoteAdress, unsigned short remotePort);

    void receive(sf::Packet &packet);
    void receive(sf::Packet &packet, sf::IpAddress &remoteAddress, unsigned short &remotePort);
    void receive(const void *data, std::size_t size, sf::IpAddress &remoteAddress, unsigned short &remotePort);


    void send(const sf::Packet &packet);
    void send(const void *data, std::size_t size);
    void send(const sf::Packet &packet, const sf::IpAddress &remoteAddress, unsigned short remotePort);
    void send(const void *data, std::size_t size, const sf::IpAddress &remoteAddress, unsigned short remotePort);


private:
    RemoteList *m_receiver;
    sf::UdpSocket m_socket;
    sf::SocketSelector m_selector;


};

#endif	/* CONNECTIONMANAGER_H */

