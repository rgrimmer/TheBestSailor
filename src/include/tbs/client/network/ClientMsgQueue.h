/* 
 * File:   ClientMsgQueue.h
 * Author: maxence
 *
 * Created on 16 décembre 2014, 17:06
 */

#ifndef CLIENTMSGQUEUE_H
#define	CLIENTMSGQUEUE_H

#include "shared/SynchronizedQueue.h"

class MessageData;

class ClientMsgQueue : public SynchronizedQueue<MessageData*> {
public:
    ClientMsgQueue();
    virtual ~ClientMsgQueue();
private:

};

#endif	/* CLIENTMSGQUEUE_H */

