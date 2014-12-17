/* 
 * File:   ServerMessageQueue.h
 * Author: maxence
 *
 * Created on 16 décembre 2014, 10:56
 */

#ifndef SERVERMESSAGEQUEUE_H
#define	SERVERMESSAGEQUEUE_H

#include "shared/SynchronizedQueue.h"
//#include "shared/network/MessageData.h"

//#include "server/ServerPlayer.h"

class ServerPlayer;
class MessageData;

class ServerMessageQueue : public SynchronizedQueue<std::pair<ServerPlayer*, MessageData*> > {
public:
    ServerMessageQueue();
    virtual ~ServerMessageQueue();
    
private:

};

#endif	/* SERVERMESSAGEQUEUE_H */

