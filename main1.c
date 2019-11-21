#include "header.h"

int getIntegerInput(void) {
	int input, num;
	fflush(stdin);
	num = scanf("%d", &input);
	
	if (num != 1) //if it fails to get integer
		input = -1;

	return input;
}

void dollarinit() { //자산dollar 50으로 초기화
	int i;
	for (i = 0;i < n_user;i++) {
		u_dollar[i] = 50;
	}
}
//card processing functions ---------------

//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) {  //크기 비교할수있도록  
	int cardvalue;
	int crest = 0;
	crest = cardnum % 13;
	if (crest >= 1 && crest <= 9)
		cardvalue = crest + 1;
	else if (crest == 10 || crest == 11 || crest == 12) cardvalue = 10;

	//A인 경우 처리  
}


//card array controllers -------------------------------

//mix the card sets and put in the array
int mixCardTray(void) {
	srand((unsigned)time(NULL));
	
	printf("------------------------------------------------\n");
	printf("------------ ROUND %d (cardIndex:0)--------------------------\n", roundNum++);
	printf("------------------------------------------------\n\n");

	int randomnumber; int i;
	int temp; int rn; int num = 52;
	int t;
	for (t = 0;t<num;t++) CardTray[t] = t + 1;
	for (i = 0;i<num - 1;i++) {
		rn = rand() % (num - i) + i;
		temp = CardTray[i];
		CardTray[i] = CardTray[rn];
		CardTray[rn] = temp;
	}

}
//get one card from the tray
int pullCard(void) {
	pullnum--;
	if (pullnum == 0) { //card다쓰면 end  
		printf("\n----cardtray is empty. gameover----\n");
		gameEnd = 1;
	}
	return pullnum;

}


//playing game functions -----------------------------

//player settiing
int configUser(void) {

	do {
		printf("Input the number of players (MAX:5): ");
		n_user = getIntegerInput();
		
		if (n_user >5) printf("Too many players!\n");
		if (n_user <1) printf("invalid input players (%d)\n", n_user);
	} while (n_user>5 || n_user<1);
}



//betting
int betDollar(void) {
	printf("------- BETTING STEP -------\n");
	do {
		printf("  -> your betting (total:$%d) : ",u_dollar[0]);
		dollar[0] = getIntegerInput();
		//scanf("%d", &dollar[0]);
		if (dollar[0]>50) printf("   -> you only have $%d! bet again\n",u_dollar[0]);
		if (dollar[0]<0) printf("   -> invalid input for betting $%d\n", dollar[0]);

	} while (dollar[0]>u_dollar[0] || dollar[0]<0);
	//printf("   -> your betting (total:$50) : %d\n",dollar[0]);
	int i;

	for (i = 1;i<n_user;i++) {
		int random = rand();
		dollar[i] = random % 50 + 1;
		printf("   -> player%d bets $%d (out of $%d)\n", i, dollar[i],u_dollar[i]);
	}
	printf("\n");
}

//offering initial 2 cards
void offerCards(void) {
	printf(" ----------- CARD OFFERING ---------------\n");
	int i;
	//1. give two card for each players
	for (i = 0;i<n_user;i++) //0~n_user-1만큼 player에 
	{
		cardhold[i][0] = CardTray[pullCard()];
		cardhold[i][1] = CardTray[pullCard()];
	}
	//2. give two card for the operator
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
	for (p = 1;p<n_user;p++) {
		printf("   -> player %d 		: ", p);
		printCard(cardhold[p][0]); printf(" ");printCard(cardhold[p][1]);
		printf("\n");
	}
}

void printWhoTurn(int user) { //해당 turn의 플레이어 출력
	if (user == 0) {
		printf("\n>>> My turn!-----------\n");
	}
	else if (user == n_user) {
		printf("\n>>> server turn! -----------------\n");
	}
	else
		printf("\n>>> player %d turn! --------------\n", user);
}

void clearCardhold() { //cardhold 비우기
	int i; int j;
	for (i = 0;i <= n_user;i++) {
		for (j = 0;j < N_MAX_CARDHOLD;j++)
			cardhold[i][j] = '\0';
	}
}


void printUserCardStatus(int user) { //각 player의 card상태 출력
	int cardcnt;
	int r = 0;
	while (cardhold[user][r] != '\0') {
		r++;
	}
	cardcnt = r;

	int i;

	printf("   -> card : ");
	for (i = 0;i<cardcnt;i++) {
		printCard(cardhold[user][i]);
		printf(" ");
	}

}

//flag로 패배, 승리때 그 턴 끝나도록 

int calcCardNumber(int num) { //카드value 구하는 함수
	int cardNumber;
	if (num % 13 >= 1 && num % 13 <= 9) cardNumber = (num % 13) + 1;
	else if (num % 13 >= 10 && num % 13 <= 12) cardNumber = 10;
	else if (num % 13 == 0) {
		cardNumber = 1;
	}
	
	return cardNumber;
}

// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack

int calcStepResult(int user) { //cardsum 반환
	int cardcnt;
	int r = 0;
	while (cardhold[user][r] != '\0')
		r++;
	cardcnt = r; //cardcnt구하기

	int i;
	int cardsum = 0;
	for (i = 0;i < cardcnt;i++) { //cardsum 구하기
		cardsum += calcCardNumber(cardhold[user][i]);
		
	} 
	
	if (calcCardNumber(cardhold[user][i])==1){ //A 11 or 1 
		if ((cardsum+10) >21){
			return cardsum;
		}
		else if ((cardsum+10)<=21){
			return cardsum+10;
		}
	}
	return cardsum; 
}


int getAction(int user) {
	int choose;
	int cardcnt;
	int r = 0;
	while (cardhold[user][r] != '\0')
		r++;
	cardcnt = r; //일단 얘도 cardcnt는 구해놓긴함

	if (user == 0) {
		if (calcStepResult(0) < 21) {
			printf("\t::: Action? (0 - go, others - stay) :");
			scanf("%d", &choose);
			if (choose == 0) { //go
				cardhold[user][cardcnt] = CardTray[pullCard()];
			}
			else {
				flag = 1; //stop
			}
		}
		else if (calcStepResult(0) == 21) { //blackjack일때, 돈계산
			printf("\t::: BLACKJACK!!!\n");
			u_dollar[0] += 2 * dollar[0];
			flag = 1;
		}
		else {
			printf("\t::: DEAD (sum:%d)", calcStepResult(0));
			u_dollar[0] -= dollar[0];						//DEAD하면 여기서 돈계산들어감.
			printf(" --> -$%d ($%d)\n", dollar[0], u_dollar[0]);
			flag = 1;
		}
	}
	
	else {//dealer가 21보다 작을때  
		if (calcStepResult(user) >= 17) { //stop
			if (calcStepResult(user) == 21) {	//blackjack, 돈계산
				u_dollar[user] += 2 * dollar[user];
				printf(" ::: BLACKJACK!!!\n");
			}
			else if (calcStepResult(user) > 21) {
				printf(" ::: DEAD (sum:%d)", calcStepResult(user));
				u_dollar[user] -= dollar[user];						//DEAD하면 여기서 돈계산들어감.
				printf(" --> -$%d ($%d)\n", dollar[user], u_dollar[user]); 
			}
			else printf(" ::: STAY\n");
			flag = 1;
		}
		else if (calcStepResult(user) < 17) { //go
			printf(" ::: GO!\n");
			cardhold[user][cardcnt] = CardTray[pullCard()];
		}
	}
}


int checkResult() {
	//dealer의 카드합마다 다른 출력
	if (calcStepResult(n_user) > 21)	printf("\n[[[[[[ server result is .... overflow! ]]]]]]\n");
	else if (calcStepResult(n_user) == 21) { 
		printf("\n[[[[[[ server result is .... BLACKJACK! ]]]]]]\n");
		printf("All Player is lose! (except for blackjack player)\n");
	}
	else	printf("\n[[[[[[ server result is .... %d ]]]]]]\n", calcStepResult(n_user));

	//dealer가 블랙잭이면 당시 블랙잭인 player제외하고 모두 패배
	if (calcStepResult(n_user) == 21) {
		printf(" -> your result : ");
		if (calcStepResult(0) == 21) { //dealer가 bj일때 나부터 처리
			printf(" win (sum:21) --> $%d\n", u_dollar[0]);
		}
		else if (calcStepResult(0) > 21) {
			printf(" lose due to overflow! ($%d) \n", u_dollar[0]);
		}
		else if (calcStepResult(0) < 21) {
			u_dollar[0] -= dollar[0];
			printf(" lose! ($%d)\n", u_dollar[0]);
		}
		//player들
		int i;
		for (i = 0;i < n_user;i++) {
			printf(" -> %d player's result : ", i);
			if (calcStepResult(i) == 21) {
				printf(" win (sum:21) --> $%d\n", u_dollar[i]);

			}
			else if (calcStepResult(i) > 21) {
				printf(" lose due to overflow! ($%d) \n", u_dollar[i]);
			}
			else if (calcStepResult(i) < 21) {
				u_dollar[i] -= dollar[i];
				printf(" lose! ($%d)\n", u_dollar[i]);
			}
		}

	}
	//dealer가 overflow
	else if (calcStepResult(n_user)>21){
		printf(" -> your result : "); //you
		if (calcStepResult(0) == 21) { //블랙잭일때 win
			printf(" win (sum:21) --> $%d\n", u_dollar[0]);
		}
		else if (calcStepResult(0) > 21) {//overflow
			printf(" lose due to overflow! ($%d) \n", u_dollar[0]);
		}
		else {
			u_dollar[0]+=dollar[0];
			printf(" win (sum:%d) --> $%d\n",calcStepResult(0),u_dollar[0]);
		}
		//players
		int i;
		for (i = 1;i < n_user;i++) {
			printf(" -> %d player's result : ", i);
			if (calcStepResult(i) == 21) {
				printf(" win (sum:21) --> $%d\n", u_dollar[i]);
			}
			else if (calcStepResult(i) > 21) {
				printf(" lose due to overflow! ($%d) \n", u_dollar[i]);
			}
			else{
				u_dollar[i] += dollar[i];
				printf(" win (sum:%d) --> $%d\n", calcStepResult(i), u_dollar[i]);
			}
		}
	}
	
	 
	//dealer가 블랙잭 아닐때
	else {
		printf(" -> your result : ");
		if (calcStepResult(0) == 21) { //블랙잭일때. 위에서 돈계산 이미함
			printf(" win (sum:21) --> $%d\n", u_dollar[0]);
		}
		else if (calcStepResult(0) > 21) {//overflow일때. 위에서 돈게산 함
			printf(" lose due to overflow! ($%d) \n", u_dollar[0]);
		}
		else if (calcStepResult(0) < 21 && calcStepResult(0) >= calcStepResult(n_user)) {//win일때
			u_dollar[0] += dollar[0]; //돈계산
			printf(" win (sum:%d) --> $%d\n", calcStepResult(0), u_dollar[0]);
		}
		else { //둘다 21보다 작고 player<dealer일때 lose 
			u_dollar[0]-=dollar[0];
			printf(" lose (sum:%d)  -> $%d\n",calcStepResult(0),u_dollar[0]);
		}
		int i;
		for (i = 1;i < n_user;i++) {
			printf(" -> %d player's result : ", i);
			if (calcStepResult(i) == 21) {
				printf(" win (sum:21) --> $%d\n", u_dollar[i]);

			}
			else if (calcStepResult(i) > 21) {
				printf(" lose due to overflow! ($%d) \n", u_dollar[i]);
			}
			else if (calcStepResult(i) < 21 && calcStepResult(i) >= calcStepResult(n_user)) {
				u_dollar[i] += dollar[i];
				printf(" win (sum:%d) --> $%d\n", calcStepResult(i), u_dollar[i]);
			}
			else { //둘다 21보다 작고 player<dealer일때 lose 
			u_dollar[i]-=dollar[i];
			printf(" lose (sum:%d)  -> $%d\n",calcStepResult(i),u_dollar[i]);
			}
		}
	}
	printf("\n");
}

int checkWinner() { //최종 돈max인 사람이 winner 
	int maxDollar = 0; int i; int maxuser;
	for (i = 0;i<n_user;i++) {
		if (maxDollar<u_dollar[i]) {
			maxDollar = u_dollar[i];
			maxuser = i;
		}
	}
	printf("\n-------------THE RESULT---------------\n");
	printf("------WINNER : ");
	if (maxuser == 0) {
		printf("YOU!!!!!!!!!! CONGRATULATION!!!!\n");
	}
	else if (maxuser > 0 && maxuser < n_user) {
		printf("Player %d!!!!!!!!!!!!!!! CONGRATULATION!!!!\n", maxuser);
	}
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
	printf(" --> card is mixed and put into the tray\n\n");
	dollarinit(); //init. 
	
	
	
	//Game start --------
	do {
		
		betDollar();
		offerCards(); //1. give cards to all the players
		if (gameEnd==1){
			break;
		}
		printCardInitialStatus();
		printf("\n------------------ GAME start --------------------------");

		//each player's turn
		int i;
		for (i = 0;i <= n_user;i++) //each player
		{
			if (gameEnd==1){
				break;
			}
			printWhoTurn(i);
			flag = 0;
			while (flag != 1) //do until the player dies or player says stop
			{
				printUserCardStatus(i);
				if (gameEnd==1){
					break;
				}
				calcStepResult(i);
				if (gameEnd==1){
					break;
				}
				getAction(i);
				if (gameEnd==1){
					break;
				}
			}
			int p;
			for (p = 0;p < n_user;p++) {
				if (u_dollar[p] <= 0)
					gameEnd = 1;
			}
		}

		//result
		checkResult();
		clearCardhold();
		
	} while (gameEnd == 0);

	checkWinner();


	return 0;
}
