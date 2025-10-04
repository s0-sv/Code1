#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <limits>
#include <utility>
#include <stdexcept>

using namespace std;

class Card {
public:
    int suit;
    int rank;
    Card(int s=0, int r=0): suit(s), rank(r) {}

    auto operator<=>(const Card& other) const {
        if (rank != other.rank)
            return rank <=> other.rank;
        return suit <=> other.suit;
    }

    bool operator==(const Card& other) const = default;
};

class Deck {
public:
    int suits;
    int ranks; // default 13
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
        std::shuffle(cards.begin(), cards.end(), mt19937(random_device()()));
        pos = 0;
    }

    Card operator()() {
        if(pos >= (int)cards.size()) {
            generateDeck();
        } // if the cards are finished, we take a new deck
        return cards[pos++];
    }
};

void readInput(int &suits, int &n) {
    while (true) {
        cout << "Enter the number of suits: ";
        if (cin >> suits) break;
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "You must enter a natural number. Please try again.\n";
        }
    }

    while (true) {
        cout << "Enter the number of cards to deal: ";
        if (cin >> n) break;
        else {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "You must enter a natural number. Please try again.\n";
        }
    }
}

void splitDeck(vector<int> &deckparts, Deck &deck, int n) {
    int currenlen = 0;
    Card prev = deck();
    cout << prev.rank << " ";

    currenlen = 1;
    for(int i = 1; i < n; i++) {
        Card c = deck();
        if(!(c < prev)) { // “As long as the next card is higher than the previous one or has the same value, it is placed in the pile.”
            currenlen++;
        } else {
            deckparts.push_back(currenlen);
            currenlen = 1;
        }
        prev = c;
        cout << prev.rank << " ";
    }
    deckparts.push_back(currenlen);
    cout << "\n";
    cout << "Stack lengths: " << "\n";
    for (int len: deckparts ) {
        cout << len << " ";
        }
    cout << "\n";
}

 void computeStats(const vector<int> &deckparts, double &avg, double &median, vector<int> &modes, vector<pair<int,double>> &lengthPercent) {
    // average stack length
    double sum = 0;
    for(int len : deckparts) {
        sum += len;
    }
    avg = sum / deckparts.size(); // we can replace the sum with n


    // median
    vector<int> sortedDeck = deckparts;
    sort(sortedDeck.begin(), sortedDeck.end());
 
    if(sortedDeck.size() % 2 == 1)
        median = sortedDeck[sortedDeck.size()/2];
    else
        median = sortedDeck[sortedDeck.size()/2 - 1];

        
    // mode
    int currentLength = sortedDeck[0];
    int maxCount = 1;
    int currentCount = 1;
    modes.clear();

    for (int i = 1; i <= sortedDeck.size(); ++i) {
        if (i == sortedDeck.size() || sortedDeck[i] != currentLength) {
            double percent = 100.0 * currentCount / sortedDeck.size();
            lengthPercent.push_back({currentLength, percent});

            if (currentCount > maxCount) {
                maxCount = currentCount;
                modes.clear();
                modes.push_back(currentLength);
            } else if (currentCount == maxCount) {
                modes.push_back(currentLength);
            }

            if (i < sortedDeck.size()) {
                currentLength = sortedDeck[i];
                currentCount = 1;
            }
        } else {
            currentCount++;
        }
    }
}

void outStats(double avg, double median,  const vector<int> &modes, const vector<pair<int,double>> &lengthPercent) {
    cout << "Average stack length: " << avg << "\n";
    cout << "Median stack length: " << median << "\n";
    cout << "Mode: ";
    for (int m : modes) cout << m << " " << "\n";

    cout << "Distribution (percentages for each length):" << "\n";
    for (int i = 0; i < lengthPercent.size(); i++) {
        cout << "Length " << lengthPercent[i].first << ": " << lengthPercent[i].second << "%" << "\n";
    }
}

/*void runTests() {
    {
        cout << "===== Test 1: 4 suits, 16 cards =====\n";
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
        cout << "===== Test 2: 3 suits, 100 cards =====\n";
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
}*/

int main() {
try {
    int suits, n;
    readInput(suits, n);

    Deck deck(suits, 13);

    vector<int> deckparts;
    splitDeck(deckparts, deck, n);

    double avg, median;
    vector<int> modes;
    vector<pair<int,double>> lengthPercent;
    computeStats(deckparts, avg, median, modes, lengthPercent);
    
    outStats(avg, median, modes, lengthPercent);

    //runTests();
    
    } catch (const exception &e) {
        cerr << "An error has occurred: " << e.what() << "\n";
    } catch (...) {
        cerr << "An unknown error has occurred!\n";
    } 
    return 0;
}
