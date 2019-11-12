#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define N_CARDSET			1
#define N_CARD				52
#define N_DOLLAR			50


#define N_MAX_CARDNUM		13
#define N_MAX_USER			5
#define N_MAX_CARDHOLD		10
#define N_MAX_GO			17
#define N_MAX_BET			5

#define N_MIN_ENDCARD		30


//card tray object //cardhold에 넣어놓고 cardtray에 임의로 섞어서 넣음.
//그리고 tray로부터 꺼 냄 
int CardTray[N_CARDSET*N_CARD]; //52장 4*13 = 4*N_MAX_CARDNUM
int cardIndex = 0;							


//player info
int dollar[N_MAX_USER];						//dollars that each player has
int n_user=0;								//number of users


//play yard information
int cardhold[N_MAX_USER+1][N_MAX_CARDHOLD];	//cards that currently the players hold
int cardSum[N_MAX_USER];					//sum of the cards. player별 
int bet[N_MAX_USER];						//current betting. player별  
int gameEnd = 0; 							//game end flag. 1이면 end 

//some utility functions
int round =1;



//get an integer input from standard input (keyboard)
//return : input integer value
// (-1 is returned if keyboard input was not integer)

 
int getIntegerInput(void) {
    int input, num;
    
    num = scanf("%d", &input);
    fflush(stdin);
    if (num != 1) //if it fails to get integer
        input = -1;
    
    return input;
}


//card processing functions ---------------

//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) {  //크기 비교할수있도록  
	int cardvalue;
	int crest=0;
	crest=cardnum%13;
	if (crest>=1 && crest<=9)
		cardvalue=crest+1;
	else if (crest == 10 || crest==11 || crest==12) cardvalue=10;
	
	//A인 경우 처리  
}

//print the card information (e.g. DiaA)
void printCard(int cardnum) { 
	int quo=0; int rest=0; 
	quo=cardnum/13; rest = cardnum%13;
	switch (rest){
		case 0:
			if (quo==0) printf("HRT A");
			else if (quo==1) printf("DIA A");
			else if (quo ==2) printf("CLV A");
			else if (quo ==3) printf("SPD A");
			break;
		case 1:
			if (quo==0) printf("HRT2");
			else if (quo==1) printf("DIA2");
			else if (quo ==2) printf("CLV2");
			else if (quo ==3) printf("SPD2");
			break;
		case 2:
			if (quo==0) printf("HRT3");
			else if (quo==1) printf("DIA3");
			else if (quo ==2) printf("CLV3");
			else if (quo ==3) printf("SPD3");
			break;
		case 3:
			if (quo==0) printf("HRT4");
			else if (quo==1) printf("DIA4");
			else if (quo ==2) printf("CLV4");
			else if (quo ==3) printf("SPD4");
			break;
		case 4:
			if (quo==0) printf("HRT5");
			else if (quo==1) printf("DIA5");
			else if (quo ==2) printf("CLV5");
			else if (quo ==3) printf("SPD5");
			break;
		case 5:
			if (quo==0) printf("HRT6");
			else if (quo==1) printf("DIA6");
			else if (quo ==2) printf("CLV6");
			else if (quo ==3) printf("SPD6");
			break;
		case 6:
			if (quo==0) printf("HRT7");
			else if (quo==1) printf("DIA7");
			else if (quo ==2) printf("CLV7");
			else if (quo ==3) printf("SPD7");
			break;
		case 7:
			if (quo==0) printf("HRT8");
			else if (quo==1) printf("DIA8");
			else if (quo ==2) printf("CLV8");
			else if (quo ==3) printf("SPD8");
			break;
		case 8:
			if (quo==0) printf("HRT9");
			else if (quo==1) printf("DIA9");
			else if (quo ==2) printf("CLV9");
			else if (quo ==3) printf("SPD9");
			break;
		case 9:
			if (quo==0) printf("HRT10");
			else if (quo==1) printf("DIA10");
			else if (quo ==2) printf("CLV10");
			else if (quo ==3) printf("SPD10");
			break;
		case 10:
			if (quo==0) printf("HRT J");
			else if (quo==1) printf("DIA J");
			else if (quo ==2) printf("CLV J");
			else if (quo ==3) printf("SPD J");
			break;
		case 11:
			if (quo==0) printf("HRT Q");
			else if (quo==1) printf("DIA Q");
			else if (quo ==2) printf("CLV Q");
			else if (quo ==3) printf("SPD Q");
			break;
		case 12:
			if (quo==0) printf("HRT K");
			else if (quo==1) printf("DIA K");
			else if (quo ==2) printf("CLV K");
			else if (quo ==3) printf("SPD K");
			break;
	}
}


//card array controllers -------------------------------

//mix the card sets and put in the array
int mixCardTray(void) {
	srand((unsigned) time(NULL));
	printf(" --> card is mixed and put into the tray\n\n");
	printf("------------------------------------------------\n");
	printf("------------ ROUND %d (cardIndex:0)--------------------------\n",round++);
	printf("------------------------------------------------\n\n");
	
	int randomnumber; int i;
	int temp; int rn; int num=52;
	int t;
	for (t=0;t<num;t++) CardTray[t]=t+1;
	for (i=0;i<num-1;i++){
		rn = rand()%(num-i)+i;
		temp=CardTray[i];
		CardTray[i]=CardTray[rn];
		CardTray[rn]=temp;
		
	}
	
}

//get one card from the tray
int pullCard(void) {
	int cardnumber=52; 
	cardnumber--;
	if (cardnumber ==0){
		gameEnd=1;
	}
	return cardnumber;

}

//playing game functions -----------------------------

//player settiing
int configUser(void) {
	
	do{
		printf("Input the number of players (MAX:5): ");
		n_user=getIntegerInput();
		
		if (n_user >5) printf("Too many players!\n");
		if (n_user <1) printf("invalid input players (%d)\n",n_user);
	}while ( n_user>5 || n_user<1);
	
	n_user-=1;
}


//betting
int betDollar(void) {
	printf("------- BETTING STEP -------\n");
	do{
		printf("  -> your betting (total:$50) : ");
		dollar[0]=getIntegerInput();
		if (dollar[0]>50) printf("   -> you only have $50! bet again\n");
		if (dollar[0]<0) printf("   -> invalid input for betting $%d\n",dollar[0]);
		
	}while(dollar[0]>50 || dollar[0]<0);
	printf("   -> your betting (total:$50) : %d\n",dollar[0]);
	int i;
	
	for (i=1;i<=n_user;i++){
		int random=rand();
		dollar[n_user]=random%50+1;
		printf("   -> player%d bets $%d (out of $50)\n",i,dollar[i]);
	}
	
}



//offering initial 2 cards
void offerCards(void) {
	printf(" ----------- CARD OFFERING ---------------\n");
	int i;
	//1. give two card for each players
	for (i=0;i<n_user;i++)
	{
		cardhold[i][0] = pullCard();
		cardhold[i][1] = pullCard();
	}
	//2. give two card for the operator
	cardhold[n_user][0] = pullCard();
	cardhold[n_user][1] = pullCard();
	
	return;
}

//print initial card status
void printCardInitialStatus(void) {
	int p;
	printf(" --- server		: ");//server는 cardhold[][]에서 n_user번째  
	printCard(cardhold[n_user+1][0]); printCard(cardhold[n_user+1][1]); 
	printf("\n");
	printf("   -> you		: "); printCard(cardhold[0][0]); printCard(cardhold[0][1]);
	printf("\n");
	for (p=1;p<=n_user;p++){
		printf("   -> player %d 	:",p); 
		printCard(cardhold[p][0]); printCard(cardhold[p][1]);
		printf("\n");
	}
}

int getAction(void) { //go,stop
	
}


void printUserCardStatus(int user, int cardcnt) {
	int i;
	printf(">>> player %d turn! ------------\n",user);
	printf("   -> card : ");
	for (i=0;i<cardcnt;i++)
		printCard(cardhold[user][i]);
	printf("\t ::: ");
	printf("\n");
}



// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack
int calcStepResult() {
	
}

int checkResult() {
	
}

int checkWinner() {
	
}



int main(int argc, char *argv[]) {
	int roundIndex = 0;
	int max_user;
	int i;
	
	srand((unsigned)time(NULL));
	
	//set the number of players
	configUser();


	//Game initialization --------
	//1. players' dollar
	
	//2. card tray
	mixCardTray();



	//Game start --------
	do {
		
		betDollar();
		offerCards(); //1. give cards to all the players
		
		printCardInitialStatus();
		printf("\n------------------ GAME start --------------------------\n");
		
		//each player's turn
		int i;
		for (i=0;i<n_user;i++) //each player
		{
			while (1) //do until the player dies or player says stop
			{
				//print current card status printUserCardStatus();
				//check the card status ::: calcStepResult()
				//GO? STOP? ::: getAction()
				//check if the turn ends or not
			}
		}
		
		//result
		checkResult();
	} while (gameEnd == 0);
	
	checkWinner();
	
	
	return 0;
}
