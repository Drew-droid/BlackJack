#pragma once


#ifndef BLACKJACK_H
#define BLACKJACK_H
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>


typedef struct Dealer {
	int size;
	int* cards;

}Dealer;


//pakli letrehozasa
Dealer* CreateDeck(const char* filename);
//pakli felmutatas-teszt a foglalasra
void PrintDeck(Dealer* d);
//jatek elzarasa
void FinishGame(Dealer* d, int balance, int gamemode);
//nehezseg allitas
int SetLevel(int level);
//minimum tet meghatarozasa
int MinBet(int level);
//jatekos lapoknak foglalas
Dealer* cards(int m);
//kezdo lapok kiosztasa
Dealer *Cards_given(Dealer *deck);
//oszto kartyai
Dealer* Dealer_cards(Dealer* deck, int level);
//extra lap
Dealer* Extra_card(Dealer* deck, Dealer* player);
//dealer extra lap
Dealer* Extra_card_dealer(Dealer* deck, Dealer* dealer);



//jatek
int Game(Dealer* playercards, int bet, int balance, Dealer* deck,int level, double wl);
//kiiratas, a dealer csak 1 lapot mutat
void CurentStatus(Dealer* playercards, Dealer* dealer1, int sum_player, int sum_dealer);
//kiiratas2-dealer lapot mutat
void CurentStatus2(Dealer* playercards, Dealer* dealer1, int sum_player, int sum_dealer);
//megallas
int Stand(Dealer* playercards, Dealer* dealer1, Dealer* deck, int balance, int bet);
//double
int Double(Dealer* playercards, Dealer* dealer1, Dealer* deck, int balance, int bet);
//bet ellenorzes
int bet_check(int check, int bet, int min_bet, int balance);
//szint lepes
int level_up(int level, double wl, int balance);
//win lose draw 
double  WLD(int balance, int last_balance, double wl);

//coloring
void magenta();

void reset();

void yellow();

void red();

void green();

void blue();

void cyan();


void delay(int number_of_seconds);


//kiirasok a mainben

void Player_Balance(int base_balance,int balance);

void menu();

#endif // !BLACKJACK_H