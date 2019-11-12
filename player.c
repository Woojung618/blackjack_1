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
	//return n_user;
}


//betting
int betDollar(void) {
	printf("------- BETTING STEP -------\n");
	do{
		printf("  -> your betting (total:$50) : ");
		dollar[0]=getIntegerInput();
		if (dollar[0]>50) printf("   -> you only have $50! bet again\n");
		if (dollar[0]<0) printf("   -> invalid input for betting $%d",dollar[0]);
		
	}while(dollar[0]>50 || dollar[0]<0);
	printf("   -> your betting (total:$50) : %d",dollar[0]);
	int i;
	
	for (i=0;i<n_user;i++){
		int random=rand();
		dollar[n_user]=random%50+1;
		printf("   -> player%d bets $%d (out of $50)\n",i+1,dollar[n_user]);
	}
	
}


