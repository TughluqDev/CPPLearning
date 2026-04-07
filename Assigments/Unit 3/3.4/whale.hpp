#ifndef WHALE_HPP
#define WHALE_HPP

#include <iostream>
#include <string>
using namespace std;

class Mammal {
protected:
    string name;
    int legs;

public:
    Mammal(string n, int l) : name(n), legs(l) {}

    string getName() const { return name; }
    int getLegs() const { return legs; }
    void setName(const string& n) { name = n; }
    void setLegs(int l) { if (l >= 0) legs = l; }

    virtual void speak() {
        cout << name << " makes a sound." << endl;
    }

    virtual void display() {
        cout << "Name: " << name << ", Legs: " << legs << endl;
    }

    virtual ~Mammal() {}
};

class Whale : public Mammal {
private:
    double weightTons;

public:
    Whale(string n, double w) : Mammal(n, 0), weightTons(w) {}

    double getWeightTons() const { return weightTons; }
    void setWeightTons(double w) { if (w > 0) weightTons = w; }

    void speak() override {
        cout << getName() << " Super duper supe singing soooong" << endl;
    }

    void display() override {
        cout << "Whale - Name: " << getName() << ", Fins: " << getLegs() << ", Weight: " << weightTons << " tons" << endl;
    }
};

#endif