#include <iostream>
#include "BlackJack.h"


void printMenu();
void printCommands();
int placeBet(BlackJack&);
int dealerTurn(BlackJack&, BlackJack&);
int playerTurn(BlackJack&, BlackJack&);
void playerTurnPrint(BlackJack&, BlackJack&);
void dealerTurnPrint(BlackJack&, BlackJack&);
int dealerConditionCheck(BlackJack&, BlackJack&);
void check22Error(BlackJack&, BlackJack&);

int main()
{
    cout << "-------------------" << endl;
    cout << "Welcome to the Blackjack" << endl;
    cout << "-------------------" << endl;

    srand(time(NULL));
    string name;
    cout << "Enter your name: ";
    cin >> name;

    BlackJack player(name);
    BlackJack dealer("Dealer");

    int choice = 0, bet = 0, result = 0, final_result = 0;
    while (player.getMoney() > 0){
        player.resetCards();
        dealer.resetCards();
        printMenu();
        cin >> choice;

        switch (choice)
        {
        case 1: // Placing bet
            bet = placeBet(player);
            result = playerTurn(player,dealer);
            switch (result)
            {
            case 1: // Player gets BlackJack
                player.setMoney(bet * 3, true);
                cout << endl; 
                cout << "BlackJack!!!!" << endl; 
                cout << player.getName() << " wins the round and " << bet*3 << " dolars" << endl;
                break;
            case 2: // Player stands
                final_result = dealerTurn(player,dealer);
                switch (final_result)
                {
                case 1: // Player wins
                    player.setMoney(bet * 2, true);
                    cout << player.getName() << " wins the round and " << bet*2 << " dolars" << endl;
                    break;
                case 2: // Draw
                    cout << "It is draw" << endl;
                    cout << player.getName() << " takes the " << bet << " dolars back" << endl;
                    break;
                case 3: // Dealer wins
                    player.setMoney(bet, false);
                    cout << player.getName() << " lost the round and " << bet << " dolars" <<endl;       
                    break;             
                }
                break;
            case 3: // Player loses
                player.setMoney(bet, false);
                cout << player.getName() << " lost the round and " << bet << " dolars" <<endl;
                break;
            }
            break;
        case 2: // Print the money
            cout << "-------------------" << endl << player.getName() << " have " << player.getMoney() << " dolars" << endl;
            break;
        case 3:
            return 0;
        default: // Exit
            cout << "-------------------" << endl;
            cout << "Please enter valid choice" << endl;
            break;
        }
    }
    cout << "-------------------" << endl;
    cout << player.getName() << " have no money left to play" << endl;
    getchar();
    getchar();

    return 0;
}

void printMenu()
{
    cout << "-------------------" << endl;
    cout << "1. Place a bet" << endl;
    cout << "2. Check money" << endl;
    cout << "3. Quit" << endl;
    cout << "-------------------" << endl;
}

void printCommands()
{
    cout << "1. Hit" << endl;
    cout << "2. Stand" << endl;
    cout << "-------------------" << endl;
}

int placeBet(BlackJack& player_ref)
{
    cout << "-------------------" << endl << "Enter bet: ";
    int bet = 0;
    while(true)
    {
        cin >> bet;
        if(0 < bet && bet <= player_ref.getMoney())
            return bet;
        else
        {
            cout << "-------------------" << endl;
            cout << "Please enter a valid bet: ";
        }
    }
}

int playerTurn(BlackJack& player_ref, BlackJack& dealer_ref)
{
    player_ref.getTwoCards();
    dealer_ref.getTwoCards();
    check22Error(player_ref,dealer_ref);

    playerTurnPrint(player_ref,dealer_ref);
    if(player_ref.getTotalPoint() == 21)
        return 1;

    int command = 0;
    while(true)
    {
        if(player_ref.getTotalPoint() == 21)
            command = 2;

        else
        {
            printCommands();
            cin >> command;
        }

        switch (command)
        {
        case 1:
            cout << "-------------------" << endl;
            cout << "Dealer gives you a card" << endl;
            Sleep(1500);
            player_ref.hit();
            if(player_ref.getTotalPoint() > 21)
            {
                if(player_ref.checkAce())
                    playerTurnPrint(player_ref,dealer_ref);

                else
                {
                    playerTurnPrint(player_ref,dealer_ref);
                    return 3;
                }
            }

            else
                playerTurnPrint(player_ref,dealer_ref);

            break;
        case 2:
            cout << "-------------------" << endl;
            cout << player_ref.getName() << " choses to stand" << endl;
            return 2;
        default:
            cout << endl << "Please enter valid command" << endl;
            break;
        }
    }
}

void playerTurnPrint(BlackJack& player_ref, BlackJack& dealer_ref)
{
    cout << "-------------------" << endl;
    cout << dealer_ref.getName() << ": " << dealer_ref.getHeadPoint() << endl;
    dealer_ref.printWithClosedCard();
    cout << endl << player_ref.getName() << ": " << player_ref.getTotalPoint() << endl;
    player_ref.printCards();
    cout << "-------------------" << endl;
    Sleep(1500);
}

int dealerTurn(BlackJack& player_ref, BlackJack& dealer_ref)
{
    int condition = 0;
   
    Sleep(1500);
    cout << "-------------------" << endl;
    cout << "Dealer turns his card" << endl;
    Sleep(1500);

    condition = dealerConditionCheck(player_ref,dealer_ref);
    if(condition != 0)
        return condition;
    
    while(true){
        cout << "Dealer takes a card" << endl;
        Sleep(1500);
        dealer_ref.hit();

        if(dealer_ref.getTotalPoint() > 21)
        {
            if(dealer_ref.checkAce()) // If there is ace
            { 
                condition = dealerConditionCheck(player_ref,dealer_ref);
                if(condition != 0)
                    return condition;
            }

            else // If there is not ace
            { 
                dealerTurnPrint(player_ref,dealer_ref);
                return 1;
            }
        }

        else
        {
            condition = dealerConditionCheck(player_ref,dealer_ref);
            if(condition != 0)
                return condition;
        }  
    }
}

int dealerConditionCheck(BlackJack& player_ref, BlackJack& dealer_ref)
{ 
    dealerTurnPrint(player_ref,dealer_ref);
    if(dealer_ref.getTotalPoint() >= 17)
    {
        if(dealer_ref.getTotalPoint() > player_ref.getTotalPoint())
            return 3;

        else if(dealer_ref.getTotalPoint() == player_ref.getTotalPoint())
            return 2;

        else
            return 1;
    }

    else
        return 0;
}

void dealerTurnPrint(BlackJack& player_ref, BlackJack& dealer_ref)
{
    cout << "-------------------" << endl;
    cout << dealer_ref.getName() << ": " << dealer_ref.getTotalPoint() << endl;
    dealer_ref.printCards();
    cout << endl << player_ref.getName() << ": " << player_ref.getTotalPoint() << endl;
    player_ref.printCards();
    cout << "-------------------" << endl;
    Sleep(1500);
}

void check22Error(BlackJack& player_ref, BlackJack& dealer_ref)
{
    if(player_ref.getTotalPoint() == 22)
        player_ref.checkAce();
    
    if(dealer_ref.getTotalPoint() == 22)
        dealer_ref.checkAce();
}