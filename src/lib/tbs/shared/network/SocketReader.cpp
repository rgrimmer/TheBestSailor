/* 
 * File:   SocketReader.cpp
 * Author: maxence
 * 
 * Created on 19 octobre 2014, 11:54
 */

#include "SocketReader.h"

SocketReader::SocketReader(SocketQueuBuffer *buffer) : m_buffer(buffer)
{
}

SocketReader::SocketReader(const SocketReader& orig) {
}

SocketReader::~SocketReader() {
}

void SocketReader::setBuffer(SocketQueuBuffer *buffer) {
    m_buffer = buffer;
}

