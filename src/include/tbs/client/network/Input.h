/* 
 * File:   Input.h
 * Author: maxence
 *
 * Created on 19 janvier 2015, 18:50
 */

#ifndef INPUT_H
#define	INPUT_H

#include <bitset>
#include <SFML/System/Time.hpp>

class Input {
public:
    Input();
    Input(std::bitset<4>actions, sf::Time time);
    virtual ~Input();

    sf::Time getTime() const;
    const std::bitset<4>& getActions() const;
private:
    sf::Time m_time;
    std::bitset<4> m_actions;

};

#endif	/* INPUT_H */

