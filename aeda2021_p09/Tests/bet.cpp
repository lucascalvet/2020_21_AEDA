#include "bet.h"
#include <iostream>
#include <sstream>

using namespace std;

bool Bet::contains(unsigned num) const {
    return numbers.find(num) != numbers.end();
}

void Bet::generateBet(const vector<unsigned> &values, unsigned n) {
    unsigned size = numbers.size();
    vector<unsigned>::const_iterator value;
    for (value = values.begin(); value != values.end(); value++) {
        numbers.insert(*value);
        if (numbers.size() - size == n)
            break;
    }
}

unsigned Bet::countRights(const tabHInt &draw) const {
    unsigned count = 0;
    tabHInt::const_iterator num;
    for (num = draw.begin(); num != draw.end(); num++)
        if (contains(*num)) count++;
    return count;
}
