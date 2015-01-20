/* 
 * File:   InputPredictions.cpp
 * Author: maxence
 * 
 * Created on 19 janvier 2015, 18:48
 */
#include "client/network/Input.h"
#include "client/network/InputPredictions.h"

const int InputPredictions::maxCountPrediction = 200;
const int InputPredictions::halfCount = maxCountPrediction/2;

InputPredictions::InputPredictions()
: m_inputs()
, m_nextPos(0) {
    m_inputs.resize(200);
}

InputPredictions::~InputPredictions() {
}

void InputPredictions::add(const Input& input) {
    m_inputs[m_nextPos] = input;
    m_nextPos++;
    m_nextPos %= 200;
}

std::vector<Input> InputPredictions::getInputFrom(sf::Time time) const {
    unsigned int i;
    std::vector<Input> result;
    for(i = m_nextPos-1; i == m_nextPos; i = (i - 1 + maxCountPrediction) % 200) {
        if(m_inputs[i].getTime() == time)
            break;
    }
    // Optimisation
    /*    int half = halfCount;
    unsigned int index = (m_nextPos + half) %maxCountPrediction;
    
    while(m_inputs[index].getTime() != time) {
        half /= 2;
        if(m_inputs[index].getTime() < time) {
            index += halfCount;
        } else {
            index -= halfCount;
        }
        index %= maxCountPrediction;
    }
    */
    while(i != m_nextPos) {
        result.push_back(m_inputs[i]);
        i = (i + 1) % maxCountPrediction;
    }
    return result;
}
