#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"
#include "bst.h"

using namespace std;

BST<WordMeaning> Dictionary::getWords() const {
    return words;
}

bool WordMeaning::operator<(const WordMeaning &wm1) const {
    return this->word < wm1.word;
}

bool WordMeaning::operator==(const WordMeaning &wm1) const {
    return word == wm1.word;
}

//TODO
void Dictionary::readDictionary(ifstream &f) {
    string word, meaning;
    while (!f.eof()) {
        getline(f, word);
        getline(f, meaning);
        WordMeaning wm(word, meaning);
        words.insert(wm);
    }
}

//TODO
string Dictionary::searchFor(string word) const {
    WordMeaning wm(word, "");
    WordMeaning f_wm = words.find(wm);
    if (f_wm == WordMeaning("", "")) {
        iteratorBST<WordMeaning> it;
        string w_bef = "", m_bef = "", w_aft = "", m_aft = "";
        for (it = words.begin(); it != words.end() && *it < wm; it++) {
            w_bef = (*it).getWord();
            m_bef = (*it).getMeaning();
        }
        if (it != words.end()) {
            w_aft = (*it).getWord();
            m_aft = (*it).getMeaning();
        }
        throw WordInexistent(w_bef, m_bef, w_aft, m_aft);
    }
    return f_wm.getMeaning();
}

//TODO
bool Dictionary::correct(string word, string newMeaning) {
    WordMeaning wm(word, newMeaning);
    WordMeaning f_wm = words.find(wm);
    if (f_wm == WordMeaning("", "")) {
        words.insert(wm);
        return false;
    }
    words.remove(wm);
    words.insert(wm);
    return true;
}

//TODO
void Dictionary::print() const {
    iteratorBST<WordMeaning> it;
    for (it = words.begin(); it != words.end(); it++) {
        cout << (*it).getWord() << endl << (*it).getMeaning() << endl;
    }
}

