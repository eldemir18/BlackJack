#include <iostream>
#include "BlackJack.h"

Card::Card()
{
    int rand_num;
    rand_num = rand() % 13;
    switch (rand_num)
    {
    case 0:
        name = "Ace";
        point = 11; 
        break;
    case 1:
        name = "Two";
        point = 2;
        break;
    case 2:
        name = "Three";
        point = 3;
        break;
    case 3:
        name = "Four";
        point = 4;
        break;
    case 4:
        name = "Five";
        point = 5;
        break;
    case 5:
        name = "Six";
        point = 6;
        break;
    case 6:
        name = "Seven";
        point = 7;
        break;
    case 7:
        name = "Eight";
        point = 8;
        break;
    case 8:
        name = "Nine";
        point = 9;
        break;
    case 9:
        name = "Ten";
        point = 10;
        break;
    case 10:
        name = "Jack";
        point = 10;
        break;
    case 11:
        name = "Queen";
        point = 10;
        break;
    case 12:
        name = "King";
        point = 10;
        break;
    default:
        cout << "Random number error(NUMBER)" << endl;
        break;
    }
    int rand_num2;
    rand_num2 = rand() % 4;
    switch (rand_num2)
    {
    case 0:
        card_class = "Clubs";
        break;
    case 1:
        card_class = "Diamonds";
        break;
    case 2:
        card_class = "Hearts";
        break;
    case 3:
        card_class = "Spades";
        break;
    default:
        cout << "Random number error(CLASS) " <<  rand_num << endl;
        break;
    }
    next = NULL;
}

void Card::getCardName() const
{
    cout << name << " of " << card_class << endl;
}

int Card::getPoint() const
{
    return point;
}

void Card::setPointOne()
{
    point = 1;
}

//---------------------------------------------------------------------------------------------------------//


BlackJack::BlackJack(const string new_name)
{
    name = new_name;
    head = NULL;
    total_point = 0;
    money = 1000;
}

int BlackJack::getTotalPoint() const
{
    return total_point;
}

void BlackJack::getTwoCards()
{
    Card* card_one = new Card;
    Card* card_two = new Card;
    head = card_one;
    head->next = card_two;
    setTotalPoint();
}

int BlackJack::getMoney()
{
    return money;
}

string BlackJack::getName()
{
    return name;
}

int BlackJack::getHeadPoint() const
{
    return head->getPoint();
}

void BlackJack::setTotalPoint()
{
    total_point = 0;
    Card* traverse = head;
    while(traverse)
    {
        total_point += traverse->getPoint();
        traverse = traverse->next;
    }
}

void BlackJack::setMoney(const int value, bool plus_minus)
{
    if(plus_minus)
        money += value;
    
    else
        money -= value;
}

void BlackJack::hit()
{
    Card* traverse = head;
    Card* new_card = new Card;
    
    while(traverse->next)
        traverse = traverse->next;
    
    traverse->next = new_card;
    setTotalPoint();
}

void BlackJack::printCards()
{
    Card* traverse = head;
    while (traverse)
    {
        traverse->getCardName();
        traverse = traverse->next;
    }
}

void BlackJack::printWithClosedCard()
{
    head->getCardName();
    cout << "Closed Card" << endl;
}

bool BlackJack::checkAce()
{
    Card* traverse = head;
    while(traverse)
    {
        if(traverse->getPoint() == 11)
        {
            traverse->setPointOne();
            setTotalPoint();
            return true;
        }

        traverse = traverse->next;
    }

    return false;
}

void BlackJack::resetCards()
{
    Card* traverse = head;
    Card* prev = NULL;

    while(traverse)
    {
        prev = traverse;
        traverse = traverse->next;
        delete prev;
    }

    head = NULL;
    setTotalPoint();
}

BlackJack::~BlackJack()
{
    Card* traverse = head;
    Card* prev = NULL;

    while(traverse)
    {
        prev = traverse;
        traverse = traverse->next;
        delete prev;
    }
}