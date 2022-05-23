#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int score;
int flag1 = 0;
int flag2 = 0;
int maxflag = 0;

float totalexpense = 0;
float totalincome = 0;

float lowtrigger, midtrigger, bigtrigger, trigger;
float fuzzyexpense;
float expensesmol, expensemed, expensemax;

float max(float a, float b, float c){
	if(a > b && a > c){
		maxflag = 1;
		return a;
	}else if(b > a && b > c){
		maxflag = 2;
		return b;
	}else if(c > a && c > b){
		maxflag = 3;
		return c;
	}
}

void input(){
	int input1;
	system("cls");
	printf("Please select input type\n");
	printf("1. Savings/Income\n");
	printf("2. Expenses\n");
	printf("3. Back to menu\n");
	printf("\nPlease input your entry below\n");
	scanf("%d", &input1);
	switch(input1)
	{
		case 1:
			FILE* income;
			income = fopen("income.txt", "a+");
			system("cls");
			printf("Please enter your savings value!\n");
			char incomevalue[30];
			scanf("%s", &incomevalue);					
			fprintf(income,"%s\n", incomevalue);
			fclose(income);
			sleep(1);
			printf("Value entry succeed!\n");
			getchar();
			getchar();
			break;	
				
		case 2:
			FILE* expense;
			expense = fopen("expense.txt", "a+");
			system("cls");
			printf("please enter your expenses!\n");
			char expensevalue[30];
			scanf("%s", &expensevalue);
			fprintf(expense, "%s\n", expensevalue);
			fclose(expense);
			sleep(1);
			printf("value entry succeed!\n");
			getchar();
			getchar();
			break;
		
		case 3:
			flag1++;
	}	
}

void countIncome(){
	FILE* income;
	income = fopen("income.txt", "r");
	char readincome[60];
	int incomeflag = 0;
	int incomearray[100];
	while(fgets(readincome,60,income)){
		incomearray[incomeflag] = atoi(readincome);
		incomeflag++;
	}
	for(int i = 0; i < incomeflag; i++){
		totalincome += incomearray[i];
	}
	system("cls");
	printf("Your total income is:\n\n");
	printf("%0.f\n", totalincome);
	printf("\npress enter to continue\n");
}

void countExpense(){
	FILE* expense;
	expense = fopen("expense.txt", "r");
	char readexpense[60];
	int expenseflag = 0;
	int expensearray[100];
	while(fgets(readexpense, 60, expense)){
		expensearray[expenseflag] = atoi(readexpense);
		expenseflag++;
	}
	for(int i = 0; i < expenseflag; i++){
		totalexpense += expensearray[i];
	}
	system("cls");
	printf("Your total expense is:\n\n");
	printf("%0.f\n", totalexpense);
	printf("\npress enter to continue");
}

void view(){
	int input2;
	totalincome = 0;
	totalexpense = 0;
	system("cls");
	printf("Please select data view\n");
	printf("1. Total income\n");
	printf("2. Total expense\n");
	printf("3. Back to menu");
	printf("\nPlease input your entry below\n");
	scanf("%d",&input2);
	switch(input2)
	{
		case 1:
			{
			countIncome();
			getchar();
			getchar();
			break;
			}
			
		case 2:
			{
			countExpense();
			getchar();
			getchar();
			break;
			}
		case 3:
			flag2 ++;
	}
	
}

//FUZZY START
void fuzzylow(){
	if(totalexpense < lowtrigger){
		expensesmol = 1;
	}else if (totalexpense >= lowtrigger && totalexpense < midtrigger){
		expensesmol = (midtrigger - totalexpense) / (midtrigger - lowtrigger);
	}else if (totalexpense > midtrigger){
		expensesmol = 0;
	}
}

void fuzzymed(){
	if(totalexpense < lowtrigger){
		expensemed = 0;
	}else if (totalexpense >= lowtrigger && totalexpense < midtrigger){
		expensemed = (totalexpense - lowtrigger) / (midtrigger - lowtrigger);
	}else if (totalexpense >= midtrigger && totalexpense < bigtrigger){
		expensemed = (midtrigger - totalexpense) / (bigtrigger - midtrigger);
	}else if (totalexpense > bigtrigger){
		expensemed = 0;
	}
}

void fuzzybig(){
	if(totalexpense < midtrigger){
		expensemax = 0;
	}else if(totalexpense >= midtrigger && totalexpense < bigtrigger){
		expensemax = (totalexpense - midtrigger) / (bigtrigger - midtrigger);
	}else if (totalexpense >= bigtrigger){
		expensemax = 1;
	}
}
//FUZZY END

void evalpoint(){
	trigger = totalincome/4;
	lowtrigger = trigger;
	midtrigger = 2*trigger;
	bigtrigger = 3*trigger;
	fuzzylow();
	fuzzymed();
	fuzzybig();
	max(expensesmol, expensemed, expensemax);
	
}

void eval(){
	system("cls");
	evalpoint();
	float review;
	review = totalexpense/totalincome*100;
	switch(maxflag){
		case 1:
			printf("Your usage level is on low level, good job!\n\n");
			break;
		case 2:
			printf("Your usage level is on medium level, please take care.\n\n");
			break;
		case 3:
			printf("Your usage level is on the max level! Please refrain from using too much money!\n\n");
			break;
	}
	if(fmod(review, 1) == 0){
		printf("Your usage percentage is \n%0.f %%\n", review);
	}else{
		printf("Your usage percentage is \n%f %%\n", review);
	}
	printf("Please press enter to continue.");
	getchar();
	getchar();
}

void deletion(){
	system("cls");
	int in;
	FILE* income;
	income = fopen("income.txt", "w");
	FILE* expense;
	expense = fopen("expense.txt", "w");
	printf("Do you want to delete ALL OF YOUR DATA?\n");
	printf("this is PERMANENT and IRREVERSIBLE (input 1 to confirm, 2 to back)\n");
	scanf("%d", &in);
	if(in == 1){
		fprintf(income, " ");
		fprintf(expense, " ");
		printf("Your data has been deleted!\n");
	}
	else{
		return;
	}	
	printf("Please press enter to return\n");
	getchar();
	getchar();	
}

void viewfuzzy(){
	evalpoint();
	system("cls");
	printf("----Fuzzification result----\n");
	printf("Low expense fuzzy score: ");
	printf("%f\n", expensesmol);
	printf("Mid expense fuzzy score: ");
	printf("%f\n", expensemed);
	printf("High expense fuzzy score: ");
	printf("%f\n", expensemax);
	printf("Press enter to continue");
	getchar();
	getchar();
}

int main(){

	int menu;
	int flag = 0;


	do{	
	countExpense();
	countIncome();
	system("cls");
	printf("Welcome to Cashbox! \nPlease select the appropriate menu for your needs\n");
	printf("1. input values\n");
	printf("2. view data\n");
	printf("3. view evaluation\n");
	printf("4. delete all data\n");
	printf("5. view fuzzification results\n");
	printf("6. quit\n");
	
	printf("\nPlease input your entry below\n");
	scanf("%d", &menu);
	

		switch(menu)
		{
		case 1:
			do{
			input();		
			}while(flag1 < 1);
			break;			
		case 2:
			do{
			view();
			}while(flag2 < 1);
			break;
		case 3:
			eval();
			break;
		case 4:
			deletion();
			break;
		case 5:
			viewfuzzy();
			break;	
		case 6:
			flag++;
			printf("Thanks for using CashBox!\n");
			break;
		}

	}while(flag < 1);	

}
