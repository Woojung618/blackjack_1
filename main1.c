#include "header.h"

int getIntegerInput(void) {
	int input, num;
	fflush(stdin);
	num = scanf("%d", &input);
	
	if (num != 1) //if it fails to get integer
		input = -1;

	return input;
}

void dollarinit() { //�ڻ�dollar 50���� �ʱ�ȭ
	int i;
	for (i = 0;i < n_user;i++) {
		u_dollar[i] = 50;
	}
}
//card processing functions ---------------

//calculate the actual card number in the blackjack game
int getCardNum(int cardnum) {  //ũ�� ���Ҽ��ֵ���  
	int cardvalue;
	int crest = 0;
	crest = cardnum % 13;
	if (crest >= 1 && crest <= 9)
		cardvalue = crest + 1;
	else if (crest == 10 || crest == 11 || crest == 12) cardvalue = 10;

	//A�� ��� ó��  
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
	if (pullnum == 0) { //card�پ��� end  
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
	for (i = 0;i<n_user;i++) //0~n_user-1��ŭ player�� 
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
	printf(" --- server		: ");//server�� cardhold[][]���� n_user��°  
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

void printWhoTurn(int user) { //�ش� turn�� �÷��̾� ���
	if (user == 0) {
		printf("\n>>> My turn!-----------\n");
	}
	else if (user == n_user) {
		printf("\n>>> server turn! -----------------\n");
	}
	else
		printf("\n>>> player %d turn! --------------\n", user);
}

void clearCardhold() { //cardhold ����
	int i; int j;
	for (i = 0;i <= n_user;i++) {
		for (j = 0;j < N_MAX_CARDHOLD;j++)
			cardhold[i][j] = '\0';
	}
}


void printUserCardStatus(int user) { //�� player�� card���� ���
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

//flag�� �й�, �¸��� �� �� �������� 

int calcCardNumber(int num) { //ī��value ���ϴ� �Լ�
	int cardNumber;
	if (num % 13 >= 1 && num % 13 <= 9) cardNumber = (num % 13) + 1;
	else if (num % 13 >= 10 && num % 13 <= 12) cardNumber = 10;
	else if (num % 13 == 0) {
		cardNumber = 1;
	}
	
	return cardNumber;
}

// calculate the card sum and see if : 1. under 21, 2. over 21, 3. blackjack

int calcStepResult(int user) { //cardsum ��ȯ
	int cardcnt;
	int r = 0;
	while (cardhold[user][r] != '\0')
		r++;
	cardcnt = r; //cardcnt���ϱ�

	int i;
	int cardsum = 0;
	for (i = 0;i < cardcnt;i++) { //cardsum ���ϱ�
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
	cardcnt = r; //�ϴ� �굵 cardcnt�� ���س�����

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
		else if (calcStepResult(0) == 21) { //blackjack�϶�, �����
			printf("\t::: BLACKJACK!!!\n");
			u_dollar[0] += 2 * dollar[0];
			flag = 1;
		}
		else {
			printf("\t::: DEAD (sum:%d)", calcStepResult(0));
			u_dollar[0] -= dollar[0];						//DEAD�ϸ� ���⼭ ������.
			printf(" --> -$%d ($%d)\n", dollar[0], u_dollar[0]);
			flag = 1;
		}
	}
	
	else {//dealer�� 21���� ������  
		if (calcStepResult(user) >= 17) { //stop
			if (calcStepResult(user) == 21) {	//blackjack, �����
				u_dollar[user] += 2 * dollar[user];
				printf(" ::: BLACKJACK!!!\n");
			}
			else if (calcStepResult(user) > 21) {
				printf(" ::: DEAD (sum:%d)", calcStepResult(user));
				u_dollar[user] -= dollar[user];						//DEAD�ϸ� ���⼭ ������.
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
	//dealer�� ī���ո��� �ٸ� ���
	if (calcStepResult(n_user) > 21)	printf("\n[[[[[[ server result is .... overflow! ]]]]]]\n");
	else if (calcStepResult(n_user) == 21) { 
		printf("\n[[[[[[ server result is .... BLACKJACK! ]]]]]]\n");
		printf("All Player is lose! (except for blackjack player)\n");
	}
	else	printf("\n[[[[[[ server result is .... %d ]]]]]]\n", calcStepResult(n_user));

	//dealer�� �����̸� ��� ������ player�����ϰ� ��� �й�
	if (calcStepResult(n_user) == 21) {
		printf(" -> your result : ");
		if (calcStepResult(0) == 21) { //dealer�� bj�϶� ������ ó��
			printf(" win (sum:21) --> $%d\n", u_dollar[0]);
		}
		else if (calcStepResult(0) > 21) {
			printf(" lose due to overflow! ($%d) \n", u_dollar[0]);
		}
		else if (calcStepResult(0) < 21) {
			u_dollar[0] -= dollar[0];
			printf(" lose! ($%d)\n", u_dollar[0]);
		}
		//player��
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
	//dealer�� overflow
	else if (calcStepResult(n_user)>21){
		printf(" -> your result : "); //you
		if (calcStepResult(0) == 21) { //�����϶� win
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
	
	 
	//dealer�� ���� �ƴҶ�
	else {
		printf(" -> your result : ");
		if (calcStepResult(0) == 21) { //�����϶�. ������ ����� �̹���
			printf(" win (sum:21) --> $%d\n", u_dollar[0]);
		}
		else if (calcStepResult(0) > 21) {//overflow�϶�. ������ ���Ի� ��
			printf(" lose due to overflow! ($%d) \n", u_dollar[0]);
		}
		else if (calcStepResult(0) < 21 && calcStepResult(0) >= calcStepResult(n_user)) {//win�϶�
			u_dollar[0] += dollar[0]; //�����
			printf(" win (sum:%d) --> $%d\n", calcStepResult(0), u_dollar[0]);
		}
		else { //�Ѵ� 21���� �۰� player<dealer�϶� lose 
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
			else { //�Ѵ� 21���� �۰� player<dealer�϶� lose 
			u_dollar[i]-=dollar[i];
			printf(" lose (sum:%d)  -> $%d\n",calcStepResult(i),u_dollar[i]);
			}
		}
	}
	printf("\n");
}

int checkWinner() { //���� ��max�� ����� winner 
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
