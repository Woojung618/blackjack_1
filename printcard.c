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
			if (quo==0) printf("HRT Jack");
			else if (quo==1) printf("DIAJack");
			else if (quo ==2) printf("CLVJack");
			else if (quo ==3) printf("SPDJack");
			break;
		case 11:
			if (quo==0) printf("HRTQueen");
			else if (quo==1) printf("DIAQueen");
			else if (quo ==2) printf("CLVQueen");
			else if (quo ==3) printf("SPDQueen");
			break;
		case 12:
			if (quo==0) printf("HRTKing");
			else if (quo==1) printf("DIAKing");
			else if (quo ==2) printf("CLVKing");
			else if (quo ==3) printf("SPDKing");
			break;
	}
}

