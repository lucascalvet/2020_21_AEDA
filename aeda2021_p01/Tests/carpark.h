#include <iostream>
#include <string>
#include <vector>

using namespace std;

class InfoCard {
public:
	string name;
	bool present;
};

class CarPark {
	unsigned freePlaces;
	const unsigned capacity;
	vector<InfoCard> clients;
	const unsigned numMaxClients;
public:
	CarPark(unsigned cap, unsigned nMaxCli);
	bool addClient(const string & name);
	bool removeClient(const string & name);
	bool enter(const string & name);
	bool leave(const string & name);
	int clientPosition(const string & name) const;
	unsigned getNumPlaces() const;
	unsigned getNumMaxClients() const;
	unsigned getNumOccupiedPlaces() const;
	unsigned getNumClients() const;
};
