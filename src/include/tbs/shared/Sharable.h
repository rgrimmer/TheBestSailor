/* 
 * File:   Sharable.h
 * Author: maxence
 *
 * Created on 9 octobre 2014, 18:43
 */

#ifndef SHARABLE_H
#define	SHARABLE_H

#include <SFML/Network.hpp>

class Sharable {
public:
    Sharable();
    Sharable(const Sharable& orig);
    virtual ~Sharable();

    virtual sf::Packet serialize() = 0;
    virtual void serialize(const void **serializedData, std::size_t *sizeInBytes);

private:

};

#endif	/* SHARABLE_H */

