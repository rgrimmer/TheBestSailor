/* 
 * File:   Client.h
 * Author: maxence
 *
 * Created on 9 octobre 2014, 18:23
 */

#ifndef CLIENT_H
#define	CLIENT_H

class Client {
public:
    Client();
    Client(const Client& orig);
    virtual ~Client();
    
    void start(void);
private:

};

#endif	/* CLIENT_H */

