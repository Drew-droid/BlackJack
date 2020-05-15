#include "Functions.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

//alap lepesek-main
Dealer* CreateDeck(const char* filename)
{
	Dealer* pakli;
	pakli = (Dealer*)calloc(1, sizeof(Dealer));
	if (!pakli) {
		printf("Sikertelen foglalas!");
		exit(1);
	}
	pakli->size = 11;
	pakli->cards = (Dealer*)calloc(10, sizeof(Dealer));
	if (!pakli->cards) {
		printf("Sikertelen foglalas!");
		exit(2);
	}

	FILE* f;
	f = fopen(filename, "rt");
	for (int i = 1; i <= pakli->size; ++i) {
			fscanf(f, "%i", &pakli->cards[i]);
	}

	return pakli;
}


void PrintDeck(Dealer* d)
{
	printf("Card type ----- Number of cards\n");
	for (int i = 1; i <= d->size; ++i) {
		printf("%i", i);
		printf(" ----- ");
		printf("%i ", d->cards[i]);
		printf("\n");
	}

}


void FinishGame(Dealer* d, int balance,int gamemode)
{
	free(d->cards);
	free(d);
	int difference;
	int money = SetLevel(gamemode);
	difference = balance - money;
	if (difference<0 ) {
		
		red();
		printf("\t\t\t\t\t\t\t\t\tCash lost: %i\n", difference);
		reset();
	}
	if (difference> 0) {
		green();
		difference = balance-money;
		printf("\t\t\t\t\t\t\t\t\tCash won: %i\n", difference);
		reset();
	}
	if (balance == money) {
		yellow();
		printf("\t\t\t\t\t\t\t\t\tNo cash won, nor lost.(%i)\n", balance);
		reset();
	}
	FILE* fin;
	fin = fopen("End.txt", "rt");

	char title[333];
	int x = 0;
	printf("\n\n\n");
	while (fscanf(fin, "%[^\n]\n", &title) != EOF) {//end of file read
		if (x == 5) {
			magenta();
		}
		if (x == 4) {
			blue();
		}
		if (x == 3) {
			cyan();
		}
		if (x == 2) {
			green();
		}
		if (x == 1) {
			yellow();
		}
		if (x == 0) {
			red();
		}
		printf("\t\t\t\t\t %s\n", title);
		x += 1;
		delay(1);
	}
	printf("\n\n");





}


int SetLevel(int level)
{
	int balance = 0;
	while (level != 0) {

		switch (level) {
		case 1: balance += 1000;
			level = 0;
			break;
		/*--------------------------*/
		case 2: balance += 500;
			level = 0;
			break;
		/*--------------------------*/
		case 3: balance += 100;
			level = 0;
			break;
		}

	}

	return balance;
}


int MinBet(int level)
{
	int minbet= 0;
	while (level != 0) {

		switch (level) {
		case 1: minbet += 40;
			level = 0;
			break;
			/*--------------------------*/
		case 2: minbet += 50;
			level = 0;
			break;
			/*--------------------------*/
		case 3: minbet += 20;
			level = 0;
			break;
		}

	}

	return minbet;

	
}





//jatekos lapjainak legeneralasa
Dealer* cards(int m)
{
	Dealer* player;
	player = (Dealer*)calloc(1, sizeof(Dealer));
	if (!player) {
		printf("Sikertelen foglalas!");
		exit(3);
	}
	player->size = m;
	player->cards= (Dealer*)calloc(m, sizeof(Dealer));
	if (!player->cards) {
		printf("Sikertelen foglalas!");
		exit(4);
	}
	return player;
}


Dealer * Cards_given( Dealer *deck)
{

	Dealer* p;
	p = cards(2);
	int sum = 0;
	int k;
	srand(time(NULL));
	//printf("\tStarting  cards: ");
	for (int i = 0; i <p->size; ++i) {
		p->cards[i] = rand() % 10+ 2;
		k = p->cards[i];
		sum += p->cards[i];
		if (p->cards[i] == 11) {
			if (sum > 21) {
				sum -= p->cards[i];
				p->cards[i] = 1;
				sum += p->cards[i];
				deck->cards[i] -= 1;
			}

		}
		deck->cards[k] -= 1;
		/*delay(0.5);
		printf("%i\t", p->cards[i]);*/
	}
	
	/*delay(0.5);
	printf("\n\tCards total sum: %i\n", sum);*/




	return p;
}


Dealer* Dealer_cards(Dealer* deck, int level)
{

	Dealer* p;
	p = cards(2);
	int sum = 0;
	int k;
	int s;
	/*-------nehezsegi szint beallitas---------*/
	while (level != 0) {

		switch (level) {
		case 1: s = 1;
			level = 0;
			break;
			/*--------------------------*/
		case 2: s=3;
			level = 0;
			break;
			/*--------------------------*/
		case 3: s = 5;
			level = 0;
			break;
		}

	}
	/*---------------------------------------*/
	int x = 0;
	srand(time(NULL));
	//printf("\tStarting  card for the dealer: ");
	for (int i = 0; i < p->size; ++i) {
		x = rand() % 10 + s;
		if ( x<= 11) {
			p->cards[i] = x;
			k = p->cards[i];
			sum += p->cards[i];
			if (p->cards[i] == 11) {
				if (sum > 21) {
					sum -= p->cards[i];
					p->cards[i] = 1;
					sum += p->cards[i];
					deck->cards[i] -= 1;
				}

			}
			deck->cards[k] -= 1;
		}
		else { --i; }
	}

	//printf("%i\t", p->cards[1]);


	return p;
}


Dealer* Extra_card(Dealer* deck, Dealer* player)
{
	Dealer* p;
	int b = player->size + 1;
	p = cards(b);
	int sum = 0;
	int k;
	srand(time(NULL));
	for (int i = 0; i < player->size; ++i) {
		p->cards[i] = player->cards[i];
	}

	for (int i = 0; i < p->size; ++i) {
		sum += player->cards[i];
		if (p->cards[i]==0) {
			p->cards[i] = rand() % 10 + 2;
			k = p->cards[i];
			sum += p->cards[i];
			deck->cards[k] -= 1;
		}
		if (p->cards[i] == 11) {
			if (sum > 21) {
				sum -= p->cards[i];
				p->cards[i] = 1;
				sum += p->cards[i];
			}
		}

	}



	return p;
}




//jatek fgv-ek
void CurentStatus(Dealer* playercards, Dealer* dealer1, int sum_player, int sum_dealer)
{

	/*-----player-----*/
	printf("\n");
	printf("\n\t\t\t\t\t\t\t\t\t\tPlayer cards: ");
	for (int i = 0; i < playercards->size; ++i) {
		sum_player += playercards->cards[i];
		delay(1);
		printf("%i\t", playercards->cards[i]);

	}
	delay(1);
	printf("\n\t\t\t\t\t\t\t\t\t\tPlayer cards sum: %i\n", sum_player);

	/*-----dealer-----*/
	delay(1);
	printf("\n\t\t\t\t\t\t\t\t\t\tDealer cards: ");
	delay(1);
	printf("%i\t", dealer1->cards[1]);
	/*for (int i = 0; i < dealer1->size; ++i) {
		printf("%i\t", dealer1->cards[i]);
	}
	*/
	/*for (int i = 0; i < dealer1->size; ++i) {
		sum_dealer += dealer1->cards[i];
	}*/
	sum_dealer = dealer1->cards[1];
	delay(1);
	printf("\n\t\t\t\t\t\t\t\t\t\tDealers cards sum: %i\n", sum_dealer);



}

//vegso kiiratas a jatek befejeztevel
void CurentStatus2(Dealer* playercards, Dealer* dealer1, int sum_player, int sum_dealer)
{

	/*-----player-----*/
	printf("\n");
	printf("\n\t\t\t\t\t\t\t\t\t\tPlayer cards: ");
	for (int i = 0; i < playercards->size; ++i) {
		sum_player += playercards->cards[i];
		printf("%i\t", playercards->cards[i]);

	}
	printf("\n\t\t\t\t\t\t\t\t\t\tPlayer cards sum: %i\n", sum_player);

	/*-----dealer-----*/
	delay(1);
	printf("\n\t\t\t\t\t\t\t\t\t\tDealer cards: ");
	for (int i = 0; i < dealer1->size; ++i) {
		sum_dealer += dealer1->cards[i];
		delay(1);
		printf("%i\t", dealer1->cards[i]);
	}
	delay(1);
	printf("\n\t\t\t\t\t\t\t\t\t\tDealers cards sum: %i\n", sum_dealer);
	delay(2);


}

int Stand(Dealer* playercards, Dealer* dealer1, Dealer* deck, int balance, int bet)
{
	int sum_player = 0;
	int sum_dealer = 0;
	int b = 0;
	//jatekos lapjainak osszeadasa
	for (int i = 0; i < playercards->size; ++i) {
		sum_player += playercards->cards[i];
	}

	//dealer lapjainka osszeadasa
	for (int i = 0; i < dealer1->size; ++i) {
		sum_dealer += dealer1->cards[i];
	}


	red();
	printf("\n\t\t\t\t\t\t\t\t\t\tRound over.");
	reset();
	if (sum_player > 21) {
		balance -=  bet;
		red();
		printf("\n\t\t\t\t\t\t\t\t\t\tPLAYER LOST.-%i", bet);
		delay(2);
		return balance;
	}
	
	if (sum_player < sum_dealer) {
		balance -=bet ;
		red();
		printf("\n\t\t\t\t\t\t\t\t\t\tPLAYER LOST. -%i", bet);
		delay(2);
		return balance;
	}

	if (sum_player == sum_dealer) {
		balance =balance;
		yellow();
		printf("\n\t\t\t\t\t\t\t\t\t\tDRAW.");
		delay(2);
		return balance;
	}

	if (sum_player > sum_dealer) {
		balance += bet;
		green();
		printf("\n\t\t\t\t\t\t\t\t\t\tPLAYER WON. +%i", bet);
		delay(2);
		return balance;
	}


}

int Double(Dealer* playercards, Dealer* dealer1, Dealer* deck, int balance, int bet)
{
	int sum_player = 0;
	int sum_dealer = 0;
	int b;
	//jatekos lapjainak osszeadasa
	for (int i = 0; i < playercards->size; ++i) {
		sum_player += playercards->cards[i];
	}

	//dealer lapjainka osszeadasa
	for (int i = 0; i < dealer1->size; ++i) {
		sum_dealer += dealer1->cards[i];
	}

	red();
	printf("\n\t\t\t\t\t\t\t\t\t\tRound over.");
	if (sum_player > 21) {
		balance -=2* bet;
		b = 2*bet;
		red();
		printf("\n\t\t\t\t\t\t\t\t\t\tPLAYER LOST.-%i", b);
		delay(2);
		return balance;
	}

	if (sum_player < sum_dealer) {
		balance -=2* bet;
		b = (-2) * bet;
		red();
		printf("\n\t\t\t\t\t\t\t\t\t\tPLAYER LOST.%i", b);
		delay(2);
		return balance;
	}

	if (sum_player == sum_dealer) {
		balance = balance;
		yellow();
		printf("\n\t\t\t\t\t\t\t\t\t\tDRAW.");
		delay(2);
		return balance;
	}

	if (sum_player > sum_dealer) {
		balance +=2* bet;
		b = 2 * bet;
		green();
		printf("\n\t\t\t\t\t\t\t\t\t\tPLAYER WON.%i", b);
		delay(2);
		return balance;
	}


}

int bet_check(int check, int bet, int min_bet, int balance)
{
	
	if (bet < min_bet) {
		red();
		printf("\t\t\t\t\t\t\t\t\t\tNot enough bet made!");
		check += 24;
		reset();
		delay(2);
		system("CLS");
		
	}
	if (bet > balance) {
		red();
		printf("\t\t\t\t\t\t\t\t\t\tNot enough chips to bet!");
		check += 24;
		reset();
		delay(2);
		system("CLS");
	}

	return check;
}

int level_up(int level, double wl, int balance)
{
	int base_balance = SetLevel(level);
	int y=0;
	if (wl >= 2 && balance >= base_balance) {
		magenta();
		printf("\n\t\t\t\t\t\t\t\t\t\tDo you want to set a new level?");
		printf("\n\t\t\t\t\t\t\t\t\t\t1.Yes\n\t\t\t\t\t\t\t\t\t\t0.No\n");
		scanf("%i", &y);
		if (y == 1) {
			printf("\t\t\t\t\t\t\t\t\t\tCHOOSE YOUR LEVEL:\n\n\t\t\t\t\t\t\t\t\t\t 1.AMATEUR\n\n\t\t\t\t\t\t\t\t\t\t2.PROFESSIONAL\n\n\t\t\t\t\t\t\t\t\t\t3.WORD CLASS\n");
			scanf("%i", &level);
			printf("\t\t\t\t\t\t\t\t\t\tNew level set is done.");
			delay(2);
			return level;
		}
		else { return level; }
	}


	return level;
}

double WLD(int balance, int last_balance, double wl)
{
	if (last_balance < balance) {
		wl += 1;
		return wl;
	}

	if (last_balance > balance) {
		wl -= 1;
		return wl;
	}

	if (last_balance == balance) {
		wl += 0.5;
		return wl;
	}


	return wl;
}




int Game(Dealer* playercards, int bet, int balance, Dealer* deck, int level, double wl) {


	Dealer* dealer1 = Dealer_cards(deck, level);
	int sum = 0;
	int sum_d = 0;
	int b = balance;
	int sum_player = 0;
	int sum_dealer = 0;
	int step = 23;
	int last_step = 0;
	int x=0;
	int anti_double = 0;
	int last_balance = balance;


	//lapok megszamolasa, blackjack eseten a jatek instant megall
	for (int i = 0; i < playercards->size; ++i) {
		sum += playercards->cards[i];
	}
	for (int i = 0; i < dealer1->size; ++i) {
		sum_d += dealer1->cards[i];
	}
	//teszteles: sum_d = 21;
	if (sum == 21 || sum_d==21) { step = 1; }


	
	while (step != 0) {
			sum_player = 0;
			sum_dealer = 0;
			x = 0;

		switch (step) {
			/*--------------------------*/
		case 1:
			magenta();
			CurentStatus2(playercards, dealer1, sum_player, sum_dealer);
			balance = Stand(playercards, dealer1, deck, balance, bet);
			break;
			/*--------------------------*/
		case 2:
			playercards = Extra_card(deck, playercards);
			magenta();
			CurentStatus(playercards, dealer1, sum_player, sum_dealer);
			for (int i = 0; i < playercards->size; ++i) {
				sum_player += playercards->cards[i];

			}
			anti_double += 1;
			x = sum_player;
			break;
			/*--------------------------*/
		case 3:
			magenta();
			if (anti_double >= 1) { red(); delay(2); printf("\t\t\t\t\t\t\t\t\t\tNot enough credits!"); break; }
			if (2 * bet <= balance) {
				;
				playercards = Extra_card(deck, playercards);
				magenta();
				CurentStatus2(playercards, dealer1, sum_player, sum_dealer);
				balance = Double(playercards, dealer1, deck, balance, bet);
			}
			else { red(); delay(2); printf("\t\t\t\t\t\t\t\t\t\tNot enough credits!"); last_step = 23; break; }
			break;
			/*--------------------------*/
		case 23:
			magenta();
			CurentStatus(playercards, dealer1, sum_player, sum_dealer);
			break;


		}
	
		//lapok megszamolasa, blackjack eseten a jatek instant megall
		for (int i = 0; i < playercards->size; ++i) {
			sum += playercards->cards[i];
		}
		for (int i = 0; i < dealer1->size; ++i) {
			sum_d += dealer1->cards[i];
		}
		//teszteles: sum_d = 21;
		if (sum == 21 || sum_d == 21) { step = 1; continue; }

		if (step == 3 && anti_double >= 1) {
			red();
			printf("\t\t\t\t\t\t\t\t\t\tDouble down must be the first step!");
			cyan();
			delay(1);
			printf("\n\n\t\t\t\t\t\t\t\t\tSteps:\n\t\t\t\t\t\t\t\t\t\t\t11.Quit game\n\t\t\t\t\t\t\t\t\t\t\t1.Stand\n\t\t\t\t\t\t\t\t\t\t2.Hit");
			if (anti_double < 1) { printf("\n\t\t\t\t\t\t\t\t\t\t3.Double down\n"); }
			printf("\n\t\t\t\t\t\t\t\t\tNext step: ");
			scanf("%i", &step);
			system("CLS");
			continue;
		}

		if (last_step == 23) {
			step = 23;
			last_step = 0;
			system("CLS");
			continue;
		}

		if (step == 1) {
			step = 0;
			system("CLS");
			continue;
		}
		if (step == 3) {
			step = 0;
			system("CLS");
			continue;
		}
		
		if (x > 21) {
			step = 1;
			system("CLS");
			continue;
		}

		

		
		if (step!=3) {
			cyan();
			delay(1);
			printf("\n\n\t\t\t\t\t\t\t\t\tSteps:\n\t\t\t\t\t\t\t\t\t\t11.Quit game\n\t\t\t\t\t\t\t\t\t\t1.Stand\n\t\t\t\t\t\t\t\t\t\t2.Hit");
			if (anti_double < 1) {printf("\n\t\t\t\t\t\t\t\t\t\t3.Double down\n");}
			printf("\n\t\t\t\t\t\t\t\t\tNext step: ");
			scanf("%i", &step);
			system("CLS");
		}

		if (step == 0) {
			last_step = 11;
			system("CLS");
			continue;
		}
		if (step == 11) {
			last_step = step;
			step = 0;
			system("CLS");
			continue;
		}
		
		
	}

	if (last_step == 11) {
		balance -= bet;
	}




	return balance;
}


//coloring
void reset() {
	printf("\033[0m");
}

void magenta()
{
	printf("\033[0;35m");
}

void yellow(){
	printf("\033[1;33m");
}

void red() {
	printf("\033[0;31m");
}

void green() {
	printf("\033[0;32m");
}

void blue() {
	printf("\033[0;34m");
}

void cyan() {
	printf("\033[0;36m");
}


//plus
void delay(int number_of_seconds)
{
	// Converting time into milli_seconds 
	int milli_seconds = 1000 * number_of_seconds;

	// Storing start time 
	clock_t start_time = clock();

	// looping till required time is not achieved 
	while (clock() < start_time + milli_seconds)
		;
}

void Player_Balance(int base_balance, int balance)
{
	cyan();
	printf("\t\t\t\t\t\t\t\t\t\tBase balance: %i", base_balance);
	printf("\n\t\t\t\t\t\t\t\t\t\tPlayers credit: %i", balance);
}

void menu()
{
	FILE* fin;
	fin = fopen("Title.txt", "rt");
	
	char title[333];
	int x = 0;
	printf("\n\n\n");
	while (fscanf(fin, "%[^\n]\n", &title) != EOF) {//end of file read
		if (x == 0) {
			magenta();
		}
		if (x == 1) {
			blue();
		}
		if (x == 2) {
			cyan();
		}
		if (x == 3) {
			green();
		}
		if (x == 4) {
			yellow();
		}
		if (x == 5) {
			red();
		}
		printf("\t\t\t\t\t\t %s\n", title);
		x += 1;
		delay(1);
	}
	printf("\n\n");
	delay(1.5);
	yellow();
	printf("\t\t\t\t\t\t\t\t\t\tCHOOSE YOUR LEVEL:\n\n\t\t\t\t\t\t\t\t\t\t 1.AMATEUR\n\n\t\t\t\t\t\t\t\t\t\t2.PROFESSIONAL\n\n\t\t\t\t\t\t\t\t\t\t3.WORD CLASS\n");
}
