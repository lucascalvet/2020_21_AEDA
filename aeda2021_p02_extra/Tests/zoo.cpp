#include "zoo.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

unsigned Zoo::numAnimals() const {
    return animals.size();
}

unsigned Zoo::numVeterinarians() const {
    return veterinarians.size();
}

void Zoo::addAnimal(Animal *a1) {
    animals.push_back(a1);
}

string Zoo::getInfo() const {
    ostringstream info;
    vector<Animal*>::const_iterator animal;
    for (animal = animals.begin(); animal != animals.end(); animal++){
        info << (*animal)->getInfo() << endl;
    }
    return info.str();
}

bool Zoo::isYoung(string nameA) {
    vector<Animal*>::const_iterator animal;
    for (animal = animals.begin(); animal != animals.end(); animal++){
        if ((*animal)->getName() == nameA)
            return (*animal)->isYoung();
    }
    return false;
}

void Zoo::allocateVeterinarians(istream &isV) {
    string name, cod_str;
    long cod;
    while (!isV.eof()) {
        getline(isV,name);
        getline(isV,cod_str);
        cod = atoi(cod_str.c_str());
        Veterinary *v1=new Veterinary(name, cod);
        veterinarians.push_back(v1);
    }
    for (unsigned int i = 0; i < animals.size(); i++)
        animals.at(i)->setVeterinary( veterinarians[i%veterinarians.size()] );
}

bool Zoo::removeVeterinary(string nameV) {
    vector<Veterinary *>::const_iterator vet;
    for (vet = veterinarians.begin(); vet != veterinarians.end(); vet++)
        if ((*vet)->getName() == nameV){
            vector<Animal *>::const_iterator animal;
            for (animal = animals.begin(); animal != animals.end(); animal++)
                if ((*animal)->getVeterinary() == *vet)
                    if (vet + 1 == veterinarians.end())
                        (*animal)->setVeterinary(*veterinarians.begin());
                    else
                        (*animal)->setVeterinary(*(vet+1));
            veterinarians.erase(vet);
            return true;
        }
    return false;
}

bool Zoo::operator<(Zoo &zoo2) const {
    int zoo1Age = 0, zoo2Age = 0;
    vector<Animal*>::const_iterator animal;
    for (animal = animals.begin(); animal != animals.end(); animal++)
        zoo1Age += (*animal)->getAge();
    for (animal = zoo2.animals.begin(); animal != zoo2.animals.end(); animal++)
        zoo2Age += (*animal)->getAge();
    return zoo1Age < zoo2Age;
}