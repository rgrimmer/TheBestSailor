/* 
 * File:   InputPredictions.cpp
 * Author: maxence
 * 
 * Created on 19 janvier 2015, 18:48
 */
#include <iostream>

#include "client/network/Input.h"
#include "client/network/InputPredictions.h"

const int InputPredictions::maxCountPrediction = 300;

InputPredictions::InputPredictions()
: m_inputs()
, m_nextPos(0) {
    m_inputs.resize(300);
}

InputPredictions::~InputPredictions() {
}

sf::Uint32 InputPredictions::add(const Input& input) {
    sf::Uint32 id = m_nextPos;
    m_inputs[m_nextPos] = input;
    m_nextPos++;
    m_nextPos %= maxCountPrediction;
    return id;
}

std::vector<Input> InputPredictions::getInputFrom(sf::Uint32 id) const {
    std::cout << "get input" << std::endl;
    std::vector<Input> result;
    
    while(id != m_nextPos) {
        result.push_back(m_inputs[id]);
        id = (id + 1) % maxCountPrediction;
    }
    return result;
}
