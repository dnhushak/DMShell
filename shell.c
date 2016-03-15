#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "splitArgs.h"
#include "execCommand.h"
#include <sys/types.h>
#include "processHistory.h"
#include "diceRoller.h"
#include <fcntl.h>
#include "stats.h"
#define KEY_UP 72
#define KEY_DOWN 80

int main(int argc, char *argv[]) {

	initRoller();
	//User input prompt variables
	char prompt[20] = "Dungeon Master>";
	char input[300];
	char *inputArgs[30];
	int nowait;
	char buf[600];
	ProcessList * pList = (ProcessList*) malloc(sizeof(ProcessList));
	pList->size = 0;

	//Scans for argument inputs
	extern char *optarg;
	int ch;
	//Get all optional arguments using the getopt function
	while ((ch = getopt(argc, argv, "p:")) != EOF) {
		switch (ch) {
			//Prompt argument
			case 'p':
				strcpy(prompt, optarg);
				break;
		}

	}

	//Main loop
	while (1) {
		int status = 0;

		//Zero out the input buffer
		memset(&input, '\0', sizeof(input));

		//Display the shell prompt
		printf("%s ", prompt);

		/**
		 *
		 *
		 */
//		int c = 0;
//		c = getchar();
//		if (c == KEY_UP) {
//			printf("KEYUP\n");
//		} else if (c == KEY_DOWN) {
//			printf("KEYDOWN\n");
//		} else {
//			printf("\n\nKey entered: %c \n\n", c);
//		}
		/**
		 *
		 *
		 */
		//Grab input from user prompt
		fgets(input, sizeof(input), stdin);

		//Split the input line into an array of char arrays (string array)
		int numArgs;
		numArgs = splitArgs(input, inputArgs);

		//Check if a valid number of arguments have been set
		if (numArgs < 0) {
			printf("Invalid Argument(s)\n");
			continue;
		}

		//Prevent execute from attempting to execute nothing (Simply pressing enter)
		if (numArgs == 1 && !strcmp(inputArgs[0], "\0")) {
			continue;
		}

		//Check for ampersand
		if (!(strcmp(inputArgs[numArgs - 1], "&"))) {
			//Set the nowait flag
			nowait = 1;
			//Remove the ampersand from the list of arguments sent to execute
			inputArgs[numArgs - 1] = '\0';
			numArgs--;
		} else {
			nowait = 0;
		}

		//All of the checks for user input

		//exit - exit normally
		if (!(strcmp(inputArgs[0], "exit"))
				|| !(strcmp(inputArgs[0], "quit"))) {
			exit(2);
		}

		//roll - roll some dice
		else if (!(strcmp(inputArgs[0], "roll"))) {
			if (numArgs > 2
					&& (!(strcmp(inputArgs[2], "-v"))
							|| !(strcmp(inputArgs[2], "-verbose")))) {
				rollDiceCommand(inputArgs[1], 1);
			} else if (numArgs > 1) {
				rollDiceCommand(inputArgs[1], 0);
			}
		}
		// Command not found
		else {
			printf("Command not found\n");
		}
	}
}
