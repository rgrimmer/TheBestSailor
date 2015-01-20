/* 
 * File:   InputPredictions.h
 * Author: maxence
 *
 * Created on 19 janvier 2015, 18:48
 */

#ifndef INPUTPREDICTIONS_H
#define	INPUTPREDICTIONS_H

#include <vector>

class Input;

class InputPredictions {
public:
    static const int maxCountPrediction;
    
private:
    static const int halfCount;
    
public:
    InputPredictions();
    virtual ~InputPredictions();
    
    void add(const Input &input);
    std::vector<Input> getInputFrom(sf::Time time) const;
    
private:
    std::vector<Input> m_inputs;
    unsigned int m_nextPos;
};

#endif	/* INPUTPREDICTIONS_H */

