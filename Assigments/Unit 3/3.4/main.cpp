#include "whale.hpp"

int main() {
    Mammal* a = new Mammal("Generic Mammal", 4);
    Mammal* b = new Whale("Blue", 150.0);

    a->display();
    a->speak();
    b->display();
    b->speak();
}