#include <iostream>

#include "client/Client.h"

int main(int argc, char* argv[]) {
    srand(time(NULL));
    
    if (argc != 2) {
        std::cout << "Error." << std::endl;
        std::cout << "Usage : " << argv[0] << " <name>" << std::endl;
        return -1;
    }
    
    std::string name = argv[1];
    
    Client().start(name);
}