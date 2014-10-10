#include <SFML/Graphics.hpp>

#include "client/Client.h"
#include <iostream>

struct A {
    int a;
    virtual void affiche() { std::cout << "dans A\n"; }
};

struct B : public A {
    int b;
    virtual void affiche() { std::cout << "dans A\n"; }
};

int main(int argc, char* argv[]) {
    A a[1];// = new A;
    a[0] = A();
    a[0].affiche();
    //Client().start();
}