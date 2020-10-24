#include "carpark.h"
#include <vector>

using namespace std;

CarPark::CarPark(unsigned int cap, unsigned int nMaxCli) : capacity(cap),
                                                           numMaxClients(nMaxCli) {
    freePlaces = capacity;
}

unsigned CarPark::getNumPlaces() const {
    return capacity;
}

unsigned CarPark::getNumMaxClients() const {
    return numMaxClients;
}

int CarPark::clientPosition(const string &name) const {
    int index = 0;
    for (vector<InfoCard>::const_iterator cliente = clients.begin(); cliente < clients.end(); cliente++) {
        if ((*cliente).name == name)
            return index;
        index += 1;
    }
    return -1;
}

bool CarPark::addClient(const string &name) {
    if (clients.size() == numMaxClients || clientPosition(name) != -1)
        return false;
    InfoCard cliente = {name, false};
    clients.push_back(cliente);
    return true;
}

bool CarPark::enter(const string &name) {
    int pos = clientPosition(name);
    if (pos == -1 || clients.at(pos).present || freePlaces == 0)
        return false;
    clients.at(pos).present = true;
    freePlaces--;
    return true;
}

bool CarPark::removeClient(const string &name) {
    int pos = clientPosition(name);
    if (pos == -1 || clients.at(pos).present)
        return false;
    clients.erase(clients.begin() + pos);
    return true;
}

bool CarPark::leave(const string &name) {
    int pos = clientPosition(name);
    if (pos == -1 || !clients.at(pos).present)
        return false;
    clients.at(pos).present = false;
    freePlaces++;
    return true;
}

unsigned CarPark::getNumOccupiedPlaces() const {
    return capacity - freePlaces;
}

unsigned CarPark::getNumClients() const {
    return clients.size();
}