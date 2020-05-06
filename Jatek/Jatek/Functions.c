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
	printf("\nGame over.");
	int difference;
	int money = SetLevel(gamemode);
	if (balance < money) {
		difference = money - balance;
		printf("\t\tCash lost: -%i\n", difference);
	}
	if (balance > money) {
		difference = balance-money;
		printf("\t\tCash won: %i\n", difference);
	}
	if (balance == money) {
		printf("\t\tNo cash won, nor lost.(%i)\n", balance);

	}

}


int SetLevel(int level)
{
	int balance = 0;
	while (level != 0) {

		switch (level) {
		case 1: balance += 10000;
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
	printf("\tStarting  cards: ");
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
		printf("%i\t", p->cards[i]);
	}
	

	printf("\n\tCards total sum: %i\n", sum);




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
	printf("\tStarting  card for the dealer: ");
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
	printf("%i\t", p->cards[1]);


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
	printf("\n\tPlayer cards: ");
	for (int i = 0; i < playercards->size; ++i) {
		sum_player += playercards->cards[i];
		printf("%i\t", playercards->cards[i]);

	}

	printf("\n\tPlayer cards sum: %i\n", sum_player);

	/*-----dealer-----*/

	printf("\n\tDealer cards: ");
	printf("%i\t", dealer1->cards[1]);
	/*for (int i = 0; i < dealer1->size; ++i) {
		printf("%i\t", dealer1->cards[i]);
	}
	*/
	/*for (int i = 0; i < dealer1->size; ++i) {
		sum_dealer += dealer1->cards[i];
	}*/
	sum_dealer = dealer1->cards[1];
	printf("\n\tDealers cards sum: %i\n", sum_dealer);



}


void CurentStatus2(Dealer* playercards, Dealer* dealer1, int sum_player, int sum_dealer)
{

	/*-----player-----*/
	printf("\n");
	printf("\n\tPlayer cards: ");
	for (int i = 0; i < playercards->size; ++i) {
		sum_player += playercards->cards[i];
		printf("%i\t", playercards->cards[i]);

	}

	printf("\n\tPlayer cards sum: %i\n", sum_player);

	/*-----dealer-----*/

	printf("\n\tDealer cards: ");
	for (int i = 0; i < dealer1->size; ++i) {
		printf("%i\t", dealer1->cards[i]);
	}
	
	for (int i = 0; i < dealer1->size; ++i) {
		sum_dealer += dealer1->cards[i];
	}
	printf("\n\tDealers cards sum: %i\n", sum_dealer);



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

	printf("\n\tRound over.");

	if (sum_player > 21) {
		balance -=  bet;
		return balance;
	}
	
	if (sum_player < sum_dealer) {
		balance -=bet ;
		return balance;
	}

	if (sum_player == sum_dealer) {
		balance =balance;
		return balance;
	}

	if (sum_player > sum_dealer) {
		balance += bet;
		return balance;
	}


}


int Double(Dealer* playercards, Dealer* dealer1, Dealer* deck, int balance, int bet)
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


	if (sum_player > 21) {
		balance -=2* bet;
		return balance;
	}

	if (sum_player < sum_dealer) {
		balance -=2* bet;
		return balance;
	}

	if (sum_player == sum_dealer) {
		balance = balance;
		return balance;
	}

	if (sum_player > sum_dealer) {
		balance +=2* bet;
		return balance;
	}


}


int Game(Dealer* playercards, int bet, int balance, Dealer* deck, int level) {


	Dealer* dealer1 = Dealer_cards(deck, level);
	int sum = 0;
	int b = balance;
	for (int i = 0; i < playercards->size; ++i) {
		sum += playercards->cards[i];
	}
	int sum_player = 0;
	int sum_dealer = 0;
	int step = 23;
	int last_step = 0;
	int x=0;
	while (step != 0) {
			sum_player = 0;
			sum_dealer = 0;
			x = 0;
		switch (step) {
			/*--------------------------*/
		case 1:
			balance = Stand(playercards, dealer1, deck, balance, bet);
			CurentStatus2(playercards, dealer1, sum_player, sum_dealer);
			break;
			/*--------------------------*/
		case 2:
			playercards = Extra_card(deck, playercards);
			CurentStatus(playercards, dealer1, sum_player, sum_dealer);
			for (int i = 0; i < playercards->size; ++i) {
				sum_player += playercards->cards[i];

			}
			x = sum_player;
			break;
			
			/*--------------------------*/
		case 3:
			playercards = Extra_card(deck, playercards);
			balance = Double(playercards, dealer1, deck, balance, bet);
			CurentStatus2(playercards, dealer1, sum_player, sum_dealer);

			break;
			/*--------------------------*/
		case 23:
			CurentStatus(playercards, dealer1, sum_player, sum_dealer);
			break;


		}

		

		if (step == 1) {
			step = 0;
			continue;
		}
		if (step == 3) {
			step = 0;
			continue;
		}
		
		if (x > 21) {
			step = 1;
			continue;
		}

		
		if (step!=3) {
			printf("\n\nSteps:\n\t11.Quit game\n\t1.Stand\n\t2.Hit\n\t3.Double down\n");
			printf("\nNext step: ");
			scanf("%i", &step);
		}
		if (step == 11) {
			last_step = step;
			step = 0;
			continue;
		}
		
		
	}

	if (last_step == 11) {
		balance -= bet;
	}




	return balance;
}


