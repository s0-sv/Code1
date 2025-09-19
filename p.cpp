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

void readInput(int &suits, int &n) {
    while (true) {
        cout << "Введіть кількість мастей: ";
        if (cin >> suits) break;
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Треба ввести натуральне число. Спробуйте ще раз.\n";
        }
    }
    //    cout << "Введіть кількість карт в масті: ";
    //    cin >> ranks;
    while (true) {
        cout << "Введіть кількість карт для роздачі: ";
        if (cin >> n) break;
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Треба ввести натуральне число. Спробуйте ще раз.\n";
        }
    }
}

int main() {
try {
    int suits, n;
    readInput(suits, n);
    Deck deck(suits, 13); //створили нашу колоду
    } catch (const exception &e) {
        cerr << "Сталася помилка: " << e.what() << "\n";
    } catch (...) {
        cerr << "Сталася невідома помилка!\n";
    } 
    return 0;
}
