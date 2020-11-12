#include "carPark.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>

using namespace std;

bool InfoCard::operator==(const InfoCard &ic) const {
    return this->name == ic.name;
}

bool InfoCard::operator<(const InfoCard &ic) const {
    if (frequency > ic.frequency)
        return true;
    else if (frequency < ic.frequency)
        return false;
    else
        return (name < ic.name);
}

bool compName(const InfoCard &c1, const InfoCard &c2) {
    return c1.name < c2.name;
}

CarPark::CarPark(unsigned cap, unsigned nMaxCli) : capacity(cap), numMaxClients(nMaxCli) {
    freePlaces = cap;
}

vector<InfoCard> CarPark::getClients() const {
    return clients;
}

unsigned CarPark::getNumPlaces() const {
    return capacity;
}

unsigned CarPark::getNumOccupiedPlaces() const {
    return capacity - freePlaces;
}

unsigned CarPark::getNumMaxClients() const {
    return numMaxClients;
}

unsigned CarPark::getNumClients() const {
    return clients.size();
}

// TODO
int CarPark::clientPosition(const string &name) const {
    InfoCard ic;
    ic.name = name;
    return sequentialSearch(clients, ic);
}

// TODO
unsigned CarPark::getFrequency(const string &name) const {
    int pos = clientPosition(name);
    if (pos == -1) throw ClientDoesNotExist(name);
    return clients.at(pos).frequency;
}

// TODO: to modify
bool CarPark::addClient(const string &name) {
    if (clients.size() == numMaxClients) return false;
    if (clientPosition(name) != -1) return false;
    InfoCard info;
    info.name = name;
    info.present = false;
    clients.push_back(info);
    return true;
}

// TODO: to modify
bool CarPark::removeClient(const string &name) {
    for (vector<InfoCard>::iterator it = clients.begin(); it != clients.end(); it++)
        if ((*it).name == name) {
            if (!(*it).present) {
                clients.erase(it);
                return true;
            } else return false;
        }
    return false;
}

// TODO: to modify
bool CarPark::enter(const string &name) {
    if (freePlaces == 0) return false;
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (clients[pos].present) return false;
    clients[pos].present = true;
    clients.at(pos).frequency++;
    freePlaces--;
    return true;
}

// TODO: to modify
bool CarPark::leave(const string &name) {
    int pos = clientPosition(name);
    if (pos == -1) return false;
    if (!clients[pos].present) return false;
    clients[pos].present = false;
    freePlaces++;
    return true;
}


// TODO
InfoCard CarPark::getClientAtPos(unsigned p) const {
    if (p >= clients.size()) throw PositionDoesNotExist(p);
    return clients.at(p);
}

// TODO
void CarPark::sortClientsByFrequency() {
    insertionSort(clients);
}

// TODO
void CarPark::sortClientsByName() {
    sort(clients.begin(), clients.end(), compName);
}

// TODO
vector<string> CarPark::clientsBetween(unsigned f1, unsigned f2) {
    sortClientsByFrequency();
    vector<string> names;
    for (unsigned i=0; i<clients.size(); i++)
    {
        if (clients[i].frequency < f1)
            break;
        if (clients[i].frequency <= f2)
            names.push_back(clients[i].name);
    }
    return names;
}

// TODO
ostream &operator<<(ostream &os, const CarPark &cp) {
    vector<InfoCard>::const_iterator client;
    for (client = cp.clients.begin(); client != cp.clients.end(); client++) {
        os << "Name: " << client->name;
        if (client->present) os << " (is present)" ;
        os << " ; frequency = " << client->frequency << endl;
    }
    return os;
}
