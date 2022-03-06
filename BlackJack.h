#include<iostream>
#include <chrono>
#include<windows.h>

using namespace std;

class Card
{
private:
    int point;
    string name;
    string card_class;
public:
    Card* next;
    Card(); // Generating random card here
    void getCardName() const;
    int getPoint() const;
    void setPointOne(); // For ACE 11-1
};


class BlackJack
{
private:
    string name;
    Card* head;
    int total_point;
    int money;
public:
    BlackJack(const string);
    void setTotalPoint();
    void setMoney(const int, bool);
    int getTotalPoint() const;
    int getHeadPoint() const;
    int getMoney();
    string getName();
    bool checkAce();
    void resetCards();
    void getTwoCards();
    void printCards();
    void printWithClosedCard();
    void hit();
    ~BlackJack();
};

