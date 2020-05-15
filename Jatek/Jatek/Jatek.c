#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define WIN32_LEAN_AND_MEAN


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include "Functions.h"




//Zakariás Zsolt

int main() {


	Dealer* D;
	D=CreateDeck("Deck.txt");
	//PrintDeck(D);
	/*--------------------*/
	int bet;
	int min_bet;
	Dealer* c;//cards
	int last_balance = 0;
	int balance;
	int option = 1;
	int base_balance;
	double wl = 0;
	int round = 0;
	menu();
	/*-------------------*/
	
	int level;
	int base_level = 0;
	scanf("%i", &level);
	min_bet = MinBet(level);
	
	balance = SetLevel(level);
	base_balance = SetLevel(level);
	delay(1);
	printf("\t\t\t\t\t\t\t\t\tLevel selected.Let's start the game!\n");
	delay(2);
	system("CLS");
	delay(1);cyan();

	while (option != 0) {
		switch (option) {
		case 1:
			Player_Balance( base_balance, balance);
			break;
		/*-----------------------------------------------------------------------*/
		case 2:
			printf("\t\t\t\t\t\t\t\tNew Game. Make your bet(Minimum bet: %i): ", min_bet);
			scanf("%i", &bet);
		/*	if (bet < min_bet) {
				red();
				printf("\t\t\t\t\t\t\t\t\t\tNot enough bet made!");
				option = 2;
				reset();
				delay(2);
				system("CLS");
				break;
			}
			if (bet > balance) {
				red();
				printf("\t\t\t\t\t\t\t\t\t\tNot enough chips to bet!");
				option = 2;
				reset();
				delay(2);
				system("CLS");
				break;
			}*/
			int check = 0;
			check=bet_check(check, bet, min_bet, balance);
			if (check == 24) {
				option = 2;
				break;
			}
			c= Cards_given(D);
			last_balance = balance;
			balance=Game(c, bet, balance, D, level, wl);
			cyan();
			printf("\n\t\t\t\t\t\t\t\t\t\tPlayers credit: %i", balance);
			wl = WLD(balance, last_balance, wl);
			D = CreateDeck("Deck.txt");
			round += 1;
			break;

		default:
			red();
			printf("\n\t\t\t\t\t\t\t\t\t\tWrong command !");
			break;
		}
		cyan();
		printf("\n\t\t\t\t\t\t\t\t\t\tWin|lose|draw :%lf", wl);
		if (round >= 1) {
			base_level = level;
			level = level_up(level, wl, balance);
			if (base_level != level) {
				balance = SetLevel(level);
				base_balance = SetLevel(level);
				min_bet = MinBet(level);
				wl = 0;
			}
		}
		if (balance < min_bet) {
			red();
			printf("\n\t\t\t\t\t\t\t\tNot enough credits to play. Better Luck next time!\n");
			delay(5);
			option = 0;
		}
		else {
			yellow();
			printf("\n\n\t\t\t\t\t\t\t\t\t\tCommands:\n\t\t\t\t\t\t\t\t\t\t0.Quit game\n\t\t\t\t\t\t\t\t\t\t1.Player Credits\n\t\t\t\t\t\t\t\t\t\t2.New Game\n\t");
			printf("\n\t\t\t\t\t\t\t\t\t\tNew Command: ");

			scanf("%i", &option);
		}
		system("CLS");


	}
	



	FinishGame(D,balance, level);
	return 11;
}