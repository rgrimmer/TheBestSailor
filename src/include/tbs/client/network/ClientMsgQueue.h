/* 
 * File:   ClientMsgQueue.h
 * Author: maxence
 *
 * Created on 16 décembre 2014, 17:06
 */

#ifndef CLIENTMSGQUEUE_H
#define	CLIENTMSGQUEUE_H

#include "shared/SynchronizedQueue.h"

class MsgData;

class ClientMsgQueue : public SynchronizedQueue<MsgData*> {
public:
    ClientMsgQueue();
    virtual ~ClientMsgQueue();
private:

};

#endif	/* CLIENTMSGQUEUE_H */

