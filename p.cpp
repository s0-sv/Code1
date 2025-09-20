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

void splitDeck(vector<int> &deckparts, Deck &deck, int n) {
    int currenlen = 0;
    Card prev = deck(); // перша карта
    cout << prev.rank << " ";

    currenlen = 1;
    for(int i = 1; i < n; i++) {
        Card c = deck(); //витягуємо наступну карту
        if(c >= prev) { //"Поки наступна карта старша за попередню або тієї самої вартості, вона кладеться в стопку"
            currenlen++;
        } else {
            deckparts.push_back(currenlen); //зберігли довжину стопки
            currenlen = 1;
        }
        prev = c;
        cout << prev.rank << " ";
    }
    deckparts.push_back(currenlen);
    cout << "\n";
    cout << "Довжини стопок: " << "\n";
    for (int len: deckparts ) {
        cout << len << " ";
        }
    cout << "\n";
}

 void computeStats(const vector<int> &deckparts, double &avg, double &median) {
    // середня довжина стопок
    double sum = 0;
    for(int len : deckparts) {
        sum += len;
    }
    avg = sum / deckparts.size();


    // медіана
    vector<int> sortedDeck = deckparts;
    sort(sortedDeck.begin(), sortedDeck.end());
    cout << sortedDeck.size() << sortedDeck[sortedDeck.size()/2] << sortedDeck[sortedDeck.size()/2 - 1] << sortedDeck.size()/2;
    if(sortedDeck.size() % 2 == 1)
        median = sortedDeck[sortedDeck.size()/2]; // якщо непарна кількість то виводимо середній елемент як медіану
    else
        median = (sortedDeck[sortedDeck.size()/2 - 1] + sortedDeck[sortedDeck.size()/2]) / 2.0;

    }
}

int main() {
try {
    int suits, n;
    readInput(suits, n);
    Deck deck(suits, 13); //створили нашу колоду

    vector<int> deckparts; //довжини стопок в різних колодах
    splitDeck(deckparts, deck, n);
    double avg, median;

    } catch (const exception &e) {
        cerr << "Сталася помилка: " << e.what() << "\n";
    } catch (...) {
        cerr << "Сталася невідома помилка!\n";
    } 
    return 0;
}
