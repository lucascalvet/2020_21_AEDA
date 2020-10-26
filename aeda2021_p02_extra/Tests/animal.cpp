#include "animal.h"
#include <sstream>
using namespace std;

Animal::Animal(string name, int age) {
    this->name = name;
    this->age = age;
    this->vet = NULL;
    if (age < youngest) youngest = age;
}

string Animal::getName() const {
	return name;
}

int Animal::getAge() const {
    return age;
}

int Animal::youngest = INT_MAX;

int Animal::getYoungest() {
    return youngest;
}

void Animal::setVeterinary(Veterinary *vet) {
    this->vet = vet;
}

Veterinary *Animal::getVeterinary() const {
    return vet;
}

string Animal::getInfo() const {
    stringstream info;
    info << name << ", " << age;
    if (vet != NULL)
        info << ", " << vet->getInfo();
    return info.str();
}


Dog::Dog(string name, int age, string breed): Animal(name, age) {
    this->breed = breed;
}

string Dog::getInfo() const {
    stringstream info;
    info << Animal::getInfo() << ", " << breed;
    return info.str();
}

bool Dog::isYoung() const {
    return age < 5;
}

Flying::Flying(int maxv, int maxa) {
    this->maxVelocity = maxv;
    this->maxAltitude = maxa;
}

string Flying::getInfo() const {
    stringstream info;
    info << maxVelocity << ", " << maxAltitude;
    return info.str();
}

Bat::Bat(string name, int age, int maxv, int maxa): Animal(name, age), Flying(maxv, maxa) {}

string Bat::getInfo() const {
    stringstream info;
    info << Animal::getInfo() << ", " << Flying::getInfo();
    return info.str();
}

bool Bat::isYoung() const {
    return age < 4;
}