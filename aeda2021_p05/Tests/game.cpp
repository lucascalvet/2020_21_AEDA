#include "game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


unsigned int Game::numberOfWords(string phrase)
{
    if ( phrase.length() == 0 ) return 0;

    unsigned n=1;
    size_t pos = phrase.find(' ');
    while (pos != string::npos) {
        phrase = phrase.substr(pos+1);
        pos = phrase.find(' ');
        n++;
    }
    return n;
}

// TODO
Game::Game()
{
    this->kids.clear();
}

// TODO
Game::Game(list<Kid>& l2)
{
    this->kids = l2;
}

// TODO
void Game::addKid(const Kid &k1)
{
    this->kids.push_back(k1);
}

// TODO
list<Kid> Game::getKids() const
{
    return this->kids;
}

// TODO
void Game::setKids(const list<Kid>& l1)
{
    this->kids = l1;
}

// TODO
string Game::write() const
{
    ostringstream oss;
    list<Kid>::const_iterator kid;
    for (kid = kids.begin(); kid != kids.end(); kid++){
        oss << kid->write() << "\n";
    }
    return oss.str();
}

// TODO
Kid& Game::loseGame(string phrase)
{
    unsigned n_words = numberOfWords(phrase);
    list<Kid>::const_iterator kid = kids.begin();
    while (kids.size() > 1){
        for(unsigned n = (n_words-1) % kids.size(); n != 0; n--)
            kid++;
        kid = kids.erase(kid);
        if(kid == kids.end())
            kid = kids.begin();
    }
    return *kids.begin();
}

// TODO
list<Kid>& Game::reverse()
{
    kids.reverse();
    return kids;
}

// TODO
list<Kid> Game::removeOlder(unsigned id)
{
    list<Kid> removed;
    list<Kid>::const_iterator kid;

    for (kid = kids.begin(); kid != kids.end(); kid++){
        if(kid->getAge() > id){
            removed.push_back(*kid);
            kids.erase(kid);
        }
    }
    return removed;
}

// TODO
bool Game::operator==(Game& g2)
{
    if(kids.size() != g2.getKids().size())
        return false;
	return equal(kids.begin(), kids.end(), g2.getKids().begin());
}

// TODO
list<Kid> Game::shuffle() const
{
    list<Kid> res;
    list<Kid> temp_kids = this->kids;
    while(res.size() != kids.size()){
        unsigned index = rand() % temp_kids.size();
        list<Kid>::iterator it = temp_kids.begin();
        for (unsigned n = 0; n != index; n++)
            it++;
        res.push_back(*it);
        temp_kids.erase(it);
    }
    return res;
}
