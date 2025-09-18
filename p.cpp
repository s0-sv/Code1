#include <bits/stdc++.h>
using namespace std;

class Card {
public:
    int suit; //масть
    int rank; //номінал - кількість карт однієї масті (0...12)
    Card(int s=0, int r=0): suit(s), rank(r) {}

    bool operator>=(const Card& other) const {
        return (*this).rank >= other.rank;
    }
};

class Deck {
    /*int suits;
    int ranks; // за замовчуванням 13
    vector<Card> cards;
    int pos; */
public:
    int suits;
    int ranks; // за замовчуванням 13
    vector<Card> cards;
    int pos;

    Deck(int s, int r=13): suits(s), ranks(r), pos(0) {
        generateDeck();
    }

    void generateDeck() {
        cards.clear();
        for(int s=0; s<suits; s++) {
            for(int r=0; r<ranks; r++) {
                cards.push_back(Card(s,r));
            }
        }
        std::shuffle(cards.begin(), cards.end(), mt19937(random_device()())); //тасуємо
        pos = 0;
    }

    Card operator()() {
        if(pos >= (int)cards.size()) {
            generateDeck();
        } //якщо карти закінчилися то беремо нову колоду
        return cards[pos++];
    }
};

int main() {
try {
    int suits, n;
    Deck deck(suits, 13); //створили нашу колоду
    } catch (...) {
        cerr << "Сталася невідома помилка!\n";
    }
    return 0;
}
