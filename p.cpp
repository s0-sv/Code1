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

 void computeStats(const vector<int> &deckparts, double &avg, double &median, int &mode, vector<pair<int,double>> &lengthPercent) {
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



    // мода
    int currentLength = sortedDeck[0];
    mode = sortedDeck[0];
    int maxCount = 1;
    int currentCount = 1;
    for (int i = 1; i <= sortedDeck.size(); ++i) {
        if (i == sortedDeck.size() || sortedDeck[i] != currentLength) {
            double percent = 100.0 * currentCount / sortedDeck.size();
            lengthPercent.push_back({currentLength, percent}); // обчислюємо відсоток і додаємо в  lengthPercent

            if (currentCount > maxCount) {
                maxCount = currentCount;
                mode = currentLength;
            }

            if (i < sortedDeck.size()) {
                currentLength = sortedDeck[i];
                currentCount = 1;
            }
        } else { //якщо довжина така ж як і була у попередніх колод, то просто збільшуємо currentCount
            currentCount++;
        }
    }
}

void outStats(double avg, double median) {
    cout << "Середня довжина стопок: " << avg << "\n";
    cout << "Медіана довжини стопок: " << median << "\n";

    cout << "Розподіл (% для кожної довжини):" << "\n";
    for (int i = 0; i < lengthPercent.size(); i++) {
        cout << "Довжина " << lengthPercent[i].first << ": " << lengthPercent[i].second << "%" << "\n";
    }
}

void runTests() {
    {
        cout << "===== Тест 1: 4 масті, 16 карт =====\n";
        int suits = 4, n = 16;
        Deck deck(suits,13);
        vector<int> deckparts;
        splitDeck(deckparts, deck, n);
        double avg, median;
        int mode;
        vector<pair<int,double>> lengthPercent;
        computeStats(deckparts, avg, median, mode, lengthPercent);
        outStats(avg, median, mode, lengthPercent);
    }
    {
        cout << "===== Тест 2: 3 масті, 100 карт =====\n";
        int suits = 3, n = 100;
        Deck deck(suits,13);
        vector<int> deckparts;
        splitDeck(deckparts, deck, n);
        double avg, median;
        int mode;
        vector<pair<int,double>> lengthPercent;
        computeStats(deckparts, avg, median, mode, lengthPercent);
        outStats(avg, median, mode, lengthPercent);
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
    int mode;
    vector<pair<int,double>> lengthPercent; // вектор пар, де перша частина це довжина стопки, а друге це її відсоток скільки вона зустрічається
    computeStats(deckparts, avg, median, mode, lengthPercent); // рахуємо всі данні про довжини стопок
    
    outStats(avg, median, mode, lengthPercent); //виводимо результати

    runTests();
    
    } catch (const exception &e) {
        cerr << "Сталася помилка: " << e.what() << "\n";
    } catch (...) {
        cerr << "Сталася невідома помилка!\n";
    } 
    return 0;
}
