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
	PrintDeck(D);
	/*--------------------*/
	int bet;
	int min_bet;
	Dealer* c;//cards
	/*-------------------*/
	int level;
	printf("Choose your level:\n\t 1.Amateur\n\t2.Professional\n\t3.Word Class\n");
	scanf("%i", &level);
	min_bet = MinBet(level);
	int balance;
	balance = SetLevel(level);
	int base_balance = SetLevel(level);
	printf("Level selected.Let's start the game!\n");
	int option = 1;
	while (option != 0) {
		switch (option) {
		case 1:
			printf("Base balance: %i", base_balance);
			printf("\nPlayers credit: %i", balance);
			break;
		/*-----------------------------------------------------------------------*/
		case 2:
			printf("New Game. Make your bet(Minimum bet: %i): ", min_bet);
			scanf("%i", &bet);
			if (bet < min_bet) {
				printf("Not enough bet made!");
				option = 2;
				break;
			}
			if (bet > balance) {
				printf("Not enough chips to bet!");
				option = 2;
				break;
			}
			c= Cards_given(D);
			balance=Game(c, bet, balance, D, level);
			printf("\nPlayers credit: %i", balance);
			D = CreateDeck("Deck.txt");
			break;

		default:
			printf("\nWrong command !");
			break;
		}

		if (balance < min_bet) {
			printf("\n\tNot enough credits to play. Better Luck next time!\n");
			option = 0;
		}
		else {
			printf("\n\nCommands:\n\t0.Quit game\n\t1.Player Credits\n\t2.New Game\n\t");
			printf("\nNew Command: ");

			scanf("%i", &option);
		}
		system("CLS");


	}




	FinishGame(D, balance, level);
	return 11;
}