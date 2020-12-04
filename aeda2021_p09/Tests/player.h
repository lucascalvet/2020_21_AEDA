#ifndef PLAYER_H_
#define PLAYER_H_

#include "bet.h"
#include <string>

using namespace std;

struct betHash {
    int operator()(const Bet &b) const {
        int hash = 0;
        tabHInt numbers = b.getNumbers();
        tabHInt::const_iterator num;
        for (num = numbers.begin(); num != numbers.end(); num++) {
            hash += *num;
        }
        return hash;
    }

    bool operator()(const Bet &b1, const Bet &b2) const {
        if (b1.getNumbers().size() != b2.getNumbers().size()) return false;
        return b1.countRights(b2.getNumbers()) == b1.getNumbers().size();
    }
};

typedef unordered_set<Bet, betHash, betHash> tabHBet;

class Player {
    tabHBet bets;
    string name;
public:
    Player(string nm = "anonymous") { name = nm; }

    void addBet(const Bet &ap);

    unsigned betsInNumber(unsigned num) const;

    tabHBet drawnBets(const tabHInt &draw) const;

    unsigned getNumBets() const { return bets.size(); }
};

#endif 
