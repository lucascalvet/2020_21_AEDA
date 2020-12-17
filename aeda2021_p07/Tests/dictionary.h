#ifndef _DIC
#define _DIC
#include <string>
#include <fstream>
#include "bst.h"


class WordMeaning {
        string word;
        string meaning;
        public:
        WordMeaning(string w, string m): word(w), meaning(m) {}
        string getWord() const { return word; }
        string getMeaning() const { return meaning; }
        void setWord(string w) {word=w; }
        void setMeaning(string m) { meaning=m; }
        bool operator < (const WordMeaning &wm1) const;
        bool operator == (const WordMeaning &wm1) const;
};


class Dictionary
{
    BST<WordMeaning> words;
public:
    Dictionary(): words(WordMeaning("","")){};
    BST<WordMeaning> getWords() const;
    void readDictionary(ifstream &f);
    string searchFor(string word) const;
    bool correct(string word, string newMeaning);
    void print() const;
};


//TODO
class WordInexistent
{
    string word_before, meaning_before, word_after, meaning_after;
public:
    WordInexistent(string w_bef, string m_bef, string w_aft, string m_aft) : word_before(w_bef), meaning_before(m_bef),
                                                                             word_after(w_aft), meaning_after(m_aft) {}
    string getWordBefore() const { return word_before; }
    string getMeaningBefore() const { return meaning_before; }
    string getWordAfter() const { return word_after; }
    string getMeaningAfter() const { return meaning_after; }
};

#endif