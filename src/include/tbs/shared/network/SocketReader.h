/* 
 * File:   SocketReader.h
 * Author: maxence
 *
 * Created on 19 octobre 2014, 11:54
 */

#ifndef SOCKETREADER_H
#define	SOCKETREADER_H

#include "shared/network/SocketQueuBuffer.h"

class SocketReader {
public:
    SocketReader(SocketQueuBuffer *buffer);
    SocketReader(const SocketReader& orig);
    virtual ~SocketReader();
    
    void setBuffer(SocketQueuBuffer *buffer);
private:
    
    SocketQueuBuffer *m_buffer;

};

#endif	/* SOCKETREADER_H */

