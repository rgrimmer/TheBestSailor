/* 
 * File:   Client.h
 * Author: maxence
 *
 * Created on 9 octobre 2014, 18:23
 */

#ifndef CLIENT_H
#define	CLIENT_H

#include "shared/map/HeigthMap.h"

class Client {
public:
    Client();
    Client(const Client& orig);
    virtual ~Client();

    void start(void);
private:
    
private:

};

#endif	/* CLIENT_H */

