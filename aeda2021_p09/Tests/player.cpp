#include "player.h"

void Player::addBet(const Bet &b) {
    bets.insert(b);
}

unsigned Player::betsInNumber(unsigned num) const {
    unsigned count = 0;
    tabHBet::const_iterator bet;
    for (bet = bets.begin(); bet != bets.end(); bet++)
        if (bet->contains(num)) count++;
    return count;
}

tabHBet Player::drawnBets(const tabHInt &draw) const {
    tabHBet drawn;
    tabHBet::const_iterator bet;
    for (bet = bets.begin(); bet != bets.end(); bet++)
        if (bet->countRights(draw) > 3) drawn.insert(*bet);
    return drawn;
}
