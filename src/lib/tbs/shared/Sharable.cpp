/* 
 * File:   Sharable.cpp
 * Author: maxence
 * 
 * Created on 9 octobre 2014, 18:43
 */

#include "shared/Sharable.h"

Sharable::Sharable() {
}

Sharable::Sharable(const Sharable& orig) {
}

Sharable::~Sharable() {
}

void Sharable::serialize(const void ** serializedData, std::size_t *sizeInBytes) {
    sf::Packet packet = serialize();
    *serializedData = packet.getData();
    *sizeInBytes = packet.getDataSize();
}