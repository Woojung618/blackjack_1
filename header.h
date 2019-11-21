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


//get an integer input from standard input (keyboard)
//return : input integer value
// (-1 is returned if keyboard input was not integer)


 

//card tray object //cardhold�� �־���� cardtray�� ���Ƿ� ��� ����.
//�׸��� tray�κ��� �� �� 
int CardTray[N_CARDSET*N_CARD]; //52�� 4*13 = 4*N_MAX_CARDNUM
int cardIndex = 0;
int pullnum = 52;

//player info
int u_dollar[N_MAX_USER];					//dollars that each player has
int dollar[N_MAX_USER];						//dollars that each player betting
int n_user = 0;								//number of users
int userDollar[N_MAX_USER];

int roundNum = 1;
int flag = 0; //1�̸� ���� �Ǵ� �й�. �� ����.  

			  //play yard information
int cardhold[N_MAX_USER + 1][N_MAX_CARDHOLD];	//cards that currently the players hold
int cardSum[N_MAX_USER];					//sum of the cards. player�� 
int bet[N_MAX_USER];						//current betting. player��  
int gameEnd = 0;

int getIntegerInput(void);
int getCardNum(int cardnum);
void printCard(int cardnum);
int mixCardTray(void);
int pullCard(void);
int configUser(void);
int betDollar(void);
void offerCards(void);
void printCardInitialStatus(void);
int getAction(int user);
void printUserCardStatus(int user);
int calcStepResult(int user);
int checkResult(void);
int checkWinner(void);
int calcCardSum(int user);
void printWhoTurn(int user);
int calcCardNumber(int num);

