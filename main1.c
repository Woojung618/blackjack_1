#include "header.h"
 
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
	pullnum--;
	if (pullnum ==0){
		gameEnd=1;
	}
	return pullnum;

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
	//printf("   -> your betting (total:$50) : %d\n",dollar[0]);
	int i;
	
	for (i=1;i<n_user;i++){
		int random=rand();
		dollar[i]=random%50+1;
		printf("   -> player%d bets $%d (out of $50)\n",i,dollar[i]);
	}
	printf("\n");	
}



//offering initial 2 cards
void offerCards(void) {
	printf(" ----------- CARD OFFERING ---------------\n");
	int i;
	//1. give two card for each players
	for (i=0;i<n_user;i++) //0~n_user-1만큼 player에 
	{
		cardhold[i][0] = CardTray[pullCard()];
		cardhold[i][1] = CardTray[pullCard()];
	}
	//2. give two card for the operator //n_user번을 server에게? 
	cardhold[n_user][0] = CardTray[pullCard()];
	cardhold[n_user][1] = CardTray[pullCard()];
	
	return;
}

//print initial card status
void printCardInitialStatus(void) {
	int p;
	printf(" --- server		: ");//server는 cardhold[][]에서 n_user번째  
	 printf("X ");printCard(cardhold[n_user][1]); 
	printf("\n");
	printf("   -> you		: "); printCard(cardhold[0][0]); printf(" ");
	printCard(cardhold[0][1]);
	printf("\n");
	for (p=1;p<n_user;p++){
		printf("   -> player %d 		: ",p); 
		printCard(cardhold[p][0]); printf(" ");printCard(cardhold[p][1]);
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
