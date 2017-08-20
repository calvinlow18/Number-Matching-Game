#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

void printOptionModule(void);
void resetArr(int openArr[][5]);
void shuffleModule(int numArr[][5]);
void displayModule(const int openArr[4][5], const int numArr[4][5]);
void readTestModule(int openArr[4][5], const int numArr[4][5], time_t *timeStart, time_t *timeEnd);
void coordinate1(int openArr[][5], const int numArr[][5], int *row1, int *clm1);
void coordinate2(int openArr[][5], const int numArr[][5], int *row2, int *clm2);
void completeModule(const int numArr[][5], int openArr[][5], int *completeCounter, int row1, int clm1, int row2, int clm2);
void scoreModule(char allTopName[][30], time_t allTopScore[], time_t timeEnd, time_t timeStart);
void displayScoreNameModule(char allTopName[][30], time_t allTopScore[]);
void resetModule(char allTopName[][30], time_t allTopScore[]);


int main(void) {
	FILE *scoreName;
	int option, readWriteCounter;
	time_t allTopScore[5] = { 0 }, timeStart, timeEnd;
	char allTopName[5][30] = { "--------", "--------", "--------", "--------", "--------" };
	int openArr[4][5] = { 0 };
	int numArr[4][5] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	if ((scoreName = fopen("scoreName.dat", "r")) != NULL) {
		for (readWriteCounter = 0; readWriteCounter < 5; readWriteCounter++) {
			fscanf(scoreName, "%29s %d", allTopName[readWriteCounter], &allTopScore[readWriteCounter]);
		} // read scores and names file

		fclose(scoreName); // close file
	}

	do {
		system("cls");
		printf("\n     Welcome to Number Matching Game.\n\n");
		printOptionModule(); // print description of options
		do {
			printf("\n\tOption : ");
			fflush(stdin);
		} while (scanf("%d", &option) != 1 || option < 1 || option > 3); // prompt for option until valid answer is entered.
		switch (option) {
		case 1:
			system("cls");
			resetArr(openArr); // reset all openArr elements into 0
			shuffleModule(numArr); // shuffle numArr which contain predefined pairs of 0 - 9
			displayModule(openArr, numArr); // display the number matching grid.
			readTestModule(openArr, numArr, &timeStart, &timeEnd); // contain function to read in coordinate 1, coordinate 2 and comparing coordinate.
			scoreModule(allTopName, allTopScore, timeEnd, timeStart); // adjust position for new score
			displayScoreNameModule(allTopName, allTopScore); // display score and names and contain reset function.
			break;
		case 2:
			system("cls");
			displayScoreNameModule(allTopName, allTopScore); // display score and names and contain reset function.
			break;
		case 3:
			printf("\n\n\tThank you. Please come again :)\n\n"); // exit
			break;
		}
	} while (option != 3);

	scoreName = fopen("scoreName.dat", "w");

	for (readWriteCounter = 0; readWriteCounter < 5; readWriteCounter++) {
		fprintf(scoreName, "%29s %d", allTopName[readWriteCounter], allTopScore[readWriteCounter]);
	} // write score and names file. If it does not exist, it will be created.

	fclose(scoreName);

	return 0;
}

void printOptionModule(void) {
	printf("\tEnter 1 to start game.\n");
	printf("\tEnter 2 to display and reset Top 5 names and scores.\n");
	printf("\tEnter 3 to end game.\n");
}

void resetArr(int openArr[][5]) {
	int reCountRow, reCountClm;

	for (reCountRow = 0; reCountRow < 4; reCountRow++) {
		for (reCountClm = 0; reCountClm < 5; reCountClm++) {
			openArr[reCountRow][reCountClm] = 0;
		}
	}
}

void shuffleModule(int numArr[][5]) {
	int countShuR, countShuC, ranR, ranC;
	char tempN;

	srand(time(NULL));
	for (countShuR = 0; countShuR < 4; countShuR++) {
		for (countShuC = 0; countShuC < 5; countShuC++) {

			ranR = rand() % 4;
			ranC = rand() % 5;

			tempN = numArr[countShuR][countShuC];
			numArr[countShuR][countShuC] = numArr[ranR][ranC];
			numArr[ranR][ranC] = tempN;

		}
	}
}

void displayModule(const int openArr[][5], const int numArr[][5]) {
	int row, clm;
	char labelRow[4] = { 'A', 'B', 'C', 'D' };

	printf("\n\n");
	printf("%4c%5d%5d%5d%5d%5d\n\n", '\0', 1, 2, 3, 4, 5);
	for (row = 0; row < 4; row++) {
		printf("%4c", labelRow[row]);
		for (clm = 0; clm < 5; clm++) {
			if (openArr[row][clm] == 0) {
				printf("%5c", '*');
			}
			else {
				printf("%5d", numArr[row][clm]);
			}
		}
		printf("\n");
	}
}

void readTestModule(int openArr[][5], const int numArr[][5], time_t *timeStart, time_t *timeEnd) {
	int row1, clm1, row2, clm2, completeCounter = 0;

	*timeStart = time(NULL);
	do {
		coordinate1(openArr, numArr, &row1, &clm1);
		coordinate2(openArr, numArr, &row2, &clm2);
		completeModule(numArr, openArr, &completeCounter, row1, clm1, row2, clm2); // check completion.
	} while (completeCounter != 10);
	*timeEnd = time(NULL);
}

void coordinate1(int openArr[][5], const int numArr[][5], int *row1, int *clm1) {
	char tempR1;

	printf("\n\n");
	do {
		printf("    Enter 1st coordinate : ");
		fflush(stdin);
		scanf("%c", &tempR1);
		scanf("%d", clm1);
		switch (tempR1) {
		case 'A':
		case 'a':
			*row1 = 0;
			break;
		case 'B':
		case 'b':
			*row1 = 1;
			break;
		case 'C':
		case 'c':
			*row1 = 2;
			break;
		case 'D':
		case 'd':
			*row1 = 3;
			break;
		default:
			*row1 = -1;
			break;
		}
		*clm1 = *clm1 - 1;
	} while (*row1 == -1 || (*clm1 < 0 || *clm1 > 4) || openArr[*row1][*clm1] == 1);
	openArr[*row1][*clm1] = 1;
	system("cls");
	displayModule(openArr, numArr);
}

void coordinate2(int openArr[][5], const int numArr[][5], int *row2, int *clm2) {
	char tempR2;

	printf("\n\n");
	do {
		printf("    Enter 2nd coordinate : ");
		fflush(stdin);
		scanf("%c", &tempR2);
		scanf("%d", clm2);
		switch (tempR2) {
		case 'A':
		case 'a':
			*row2 = 0;
			break;
		case 'B':
		case 'b':
			*row2 = 1;
			break;
		case 'C':
		case 'c':
			*row2 = 2;
			break;
		case 'D':
		case 'd':
			*row2 = 3;
			break;
		default:
			*row2 = -1;
			break;
		}
		*clm2 = *clm2 - 1;
	} while (*row2 == -1 || (*clm2 < 0 || *clm2 > 4) || openArr[*row2][*clm2] == 1);
	openArr[*row2][*clm2] = 1;
	system("cls");
	displayModule(openArr, numArr);
}

void completeModule(const int numArr[][5], int openArr[][5], int *completeCounter, int row1, int clm1, int row2, int clm2) {
	if (numArr[row1][clm1] == numArr[row2][clm2]) {
		++*completeCounter;
	}
	else {
		openArr[row1][clm1] = 0;
		openArr[row2][clm2] = 0;
	}
}

void scoreModule(char allTopName[][30], time_t allTopScore[], time_t timeEnd, time_t timeStart) {
	time_t score, tempS;
	char name[30], tempName[30];
	int scoreLocation = 0, nsCounter, element;

	score = timeEnd - timeStart;
	printf("\n\n   Your score is %ds", score);
	Sleep(1500);
	if (allTopScore[0] == 0) {
		printf("\n\n   Congratulation! You entered Top 5.\n");
		printf("   Please enter your name: ");
		fflush(stdin);
		scanf("%29s", allTopName[0]);
		allTopScore[0] = score;
	}
	else
	{
		scoreLocation = -1;
		for (element = 0; element < 5; element++) {
			if (score < allTopScore[element]) {
				scoreLocation = element; // store location to adjust location
				break;
			} else if (score == allTopScore[element]) {
				scoreLocation = element + 1; // if same score, new score will be below old score
			} // checking in case more than 1 score is the same		
		}
		if (scoreLocation == 5) {
			scoreLocation = -1;
		} // score will not enter top 5
		if (scoreLocation != -1) {
			printf("\n\n   Congratulation! You entered Top 5.\n");
			printf("   Please enter your name: ");
			fflush(stdin);
			scanf("%29s", name);
			for (nsCounter = scoreLocation; nsCounter < 5; nsCounter++) {
				tempS = allTopScore[nsCounter];
				allTopScore[nsCounter] = score;
				score = tempS;
				strcpy(tempName, allTopName[nsCounter]);
				strcpy(allTopName[nsCounter], name);
				strcpy(name, tempName);
			}
		}
	}
}

void displayScoreNameModule(char allTopName[][30], time_t allTopScore[]) {
	int pscoreCounter, reset;

	system("cls");
	printf("\n\t*************** TOP 5 ***************\n\n\n");
	printf("\t%-30s%-7s\n\n", "Name", "Score");
	for (pscoreCounter = 0; pscoreCounter < 5; pscoreCounter++) {
		printf("\t%-30s%ds\n", allTopName[pscoreCounter], allTopScore[pscoreCounter]);
	}
	printf("\n\n\tPress 1 to reset names and scores.\n");
	printf("\tPress 2 to return to option page.\n");
	do {
		printf("\n\tOption : ");
		fflush(stdin);
	} while ((scanf("%d", &reset) != 1) || (reset != 1 && reset != 2));
	if (reset == 1) {
		resetModule(allTopName, allTopScore);
	}
}

void resetModule(char allTopName[][30], time_t allTopScore[]) {
	int resetCounter;

	for (resetCounter = 0; resetCounter < 5; resetCounter++) {
		strcpy(allTopName[resetCounter], "--------");
		allTopScore[resetCounter] = 0;
	}
}