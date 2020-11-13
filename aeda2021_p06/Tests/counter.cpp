#include <queue>
#include <cstdlib>
#include "counter.h"
#include "exceptions.h"

using namespace std;

//TODO
Client::Client() {
    this->numGifts = rand() % 5 + 1;
}

//TODO
unsigned Client::getNumGifts() const {
    return this->numGifts;
}


//TODO
Counter::Counter(unsigned wt) : wrappingTime(wt) {
    this->actualTime = 0;
    this->nextEnter = rand() % 20 + 1;
    this->nextLeave = 0;
    this->numAttendedClients = 0;
}

//TODO
unsigned Counter::getActualTime() const {
    return this->actualTime;
}

//TODO
unsigned Counter::getNextEnter() const {
    return this->nextEnter;
}

//TODO
unsigned Counter::getNumAttendedClients() const {
    return this->numAttendedClients;
}

//TODO
unsigned Counter::getWrappingTime() const {
    return wrappingTime;
}

//TODO
unsigned Counter::getNextLeave() const {
    return nextLeave;
}

//TODO
Client &Counter::getNextClient() {
    if (clients.empty()) throw EmptyQueue();
    return clients.front();
}

//TODO
void Counter::enter() {
    cout << "time = " << actualTime << endl;
    Client client;
    if (clients.empty()) nextLeave = actualTime + client.getNumGifts() * wrappingTime;
    clients.push(client);
    nextEnter = actualTime + rand() % 20 + 1;
    cout << "new customer arrived with " << client.getNumGifts() << " gifts" << endl;
}

//TODO
void Counter::leave() {
    cout << "time = " << actualTime << endl;
    Client client;
    try {
        client = getNextClient();
    }
    catch (EmptyQueue &eq) {
        cout << eq.getMsg() << endl;
        return;
    }
    clients.pop();
    cout << "client attended with " << client.getNumGifts() << " gifts" << endl;
    numAttendedClients++;
    if (!clients.empty())
        nextLeave = actualTime + clients.front().getNumGifts() * wrappingTime;
}

//TODO
void Counter::nextEvent() {
    if (!clients.empty()) {
        if (nextEnter < nextLeave) {
            actualTime = nextEnter;
            enter();
        } else {
            actualTime = nextLeave;
            leave();
        }
    } else {
        actualTime = nextEnter;
        enter();
    }
}


//TODO
ostream &operator<<(ostream &out, const Counter &counter) {
    out << "number of attended clients: " << counter.numAttendedClients << endl;
    out << "number of clients waiting: " << counter.clients.size() << endl << endl;
    return out;
}
