#include "diceRoller.h"

void initRoller() {
	/* initialize random seed: */
	srand(time(NULL));
}

int generateRandom(int min, int max) {
	// "Roll" the number
	int output = rand();
	// Scale the range
	output %= (max - min + 1);
	// Shift the range
	output += min;
	return output;
}

int rollDie(int dieSize) {
	if (dieSize < 0) {
		return 0;
	} else {
		return generateRandom(1, dieSize);
	}
}

int rollDice(int numDice, int diceSize, int modifier, int verbose) {
	// Initialize the final value
	int finalValue = 0;
	// Initialize the individual rolls
	int rollValue = 0;

	if (verbose) {
		printf(KRED "\nRolling %dd%d+%d...\n", numDice, diceSize, modifier);
		printf(KBLU "====================\n");
	}
	int i;
	for (i = 0; i < numDice; i++) {
		// Roll a singular die
		rollValue = rollDie(diceSize);
		if (verbose) {
			// Print individual roll values if verbose
			printf(KCYN "d%d Roll %d: \t%d\n", diceSize, i + 1, rollValue);
		}
		// Add each roll value to the final value
		finalValue += rollValue;
	}
	// Add the die additive parameter to the vinal value

	if (verbose && modifier != 0) {
		// Print individual roll values if verbose
		printf(KGRN "Modifier: \t%d\n", modifier);
	}
	finalValue += modifier;
	// Print the total roll value
	if (verbose) {
		printf(KBLU "====================\n");
	}
	printf(KRED "%dd%d+%d Result:" KYEL "\t%d" KNRM "\n\n", numDice, diceSize,
			modifier, finalValue);
	// Return the final value of the roll
	return finalValue;
}

int rollDiceCommand(char* rollString, int verbose) {
	// Initialize the roll parameters
	// [0] is number of dice
	// [1] is size of dice
	// [2] is die additive
	// [0]d[1] + [2]
	int params[3];
	// Initialize parameters to standard 1d6+0
	params[0] = 1;
	params[1] = 6;
	params[2] = 0;
	// Parse through the roll string, putting it in parameters
	if (parseRoll(rollString, params)) {
		rollDice(params[0], params[1], params[2], verbose);
	}
	// If parseRoll fails (returns 0),
	else {
		printf("Syntax error - please input rolls in forms of #d#+#, no spaces\n");
	}
	return -1;

}

int parseRoll(char * rollString, int * params) {
	char rollStringEdit[strlen(rollString)];
	strcpy(rollStringEdit, rollString);
	char * scanner = rollStringEdit;
	char * paramStrings[3];
	int oneDie = 0;
	int noAdd = 0;
	int isNeg = 0;

	/* Acceptable forms of input:
	 * Dice Rolls:
	 * d 6
	 * d6
	 * 1d6
	 * 1 d6
	 * 1 d 6
	 * 3d6
	 *
	 * Additive:
	 * 1d6+1
	 * 1d6 +1
	 * 1d6 + 1
	 * (any number of spaces between)
	 *
	 * Additive can be negative:
	 * 1d6+1
	 * or
	 * 1d6-1
	 *
	 */

	// Scan until first number or d
	while (*scanner != 'd' && (*scanner < '0' || *scanner > '9')) {
		// If any incorrect characters while scanning (non integer, space, newline, tab, or d) return 0 (syntax error)
		if (!checkValidChar(*scanner) || *scanner == '+' || *scanner == '-') {
			return 0;
		}
		scanner++;

	}

	if (*scanner == 'd') {
		// No number of dice given, setting oneDie indicator to 1
		oneDie = 1;
	} else {
		// Point the first parameter string to the current counter
		paramStrings[0] = scanner;

		// Advance until the end of numbers
		while (*scanner >= '0' && *scanner <= '9') {
			scanner++;
		}
	}

	// Scan until d
	while (*scanner != 'd') {
		// If any incorrect characters while scanning (non integer, space, newline, tab, or d) return 0 (syntax error)
		if (!checkValidChar(*scanner) || *scanner == '+' || *scanner == '-'
				|| isdigit(*scanner)) {
			return 0;
		}
		// Replace all the whitespace characters with null character, so paramStrings[0] knows where to stop
		*scanner = '\0';
		scanner++;

	}
	// Replace 'd' with null character
	*scanner = '\0';
	scanner++;

	// Scan until next number
	while (*scanner < '0' || *scanner > '9') {
		// If any incorrect characters while scanning (non integer, space, newline, or tab) return 0 (syntax error)
		if (!checkValidChar(*scanner) || *scanner == '+' || *scanner == '-'
				|| *scanner == 'd') {
			return 0;
		}
		scanner++;

	}

	// Point the second parameter string to the current counter
	paramStrings[1] = scanner;

	// Advance until the end of numbers
	while (*scanner >= '0' && *scanner <= '9') {
		scanner++;
	}

	// Scan until + or end
	while (*scanner != '+' && *scanner != '-' && *scanner != '\0') {
		// If any incorrect characters while scanning (non integer, space, newline, tab, or +), return 0 (syntax error)
		if (!checkValidChar(*scanner) || *scanner == 'd' || isdigit(*scanner)) {
			return 0;
		}
		// Replace all the whitespace characters with null character, so paramStrings[0] knows where to stop
		*scanner = '\0';
		scanner++;

	}

	if (*scanner == '\0') {
		// No adder/subtractor given, setting noAdd indicator to 1
		noAdd = 1;
	} else {
		// Check for minus sign
		if (*scanner == '-') {
			isNeg = 1;
		}

		*scanner = '\0';
		scanner++;

		// Scan until next number
		while (*scanner < '0' || *scanner > '9') {
			// If any incorrect characters while scanning (non integer, space, newline, or tab) return 0 (syntax error)
			if (!checkValidChar(*scanner) || *scanner == '+' || *scanner == '-'
					|| *scanner == 'd') {
				return 0;
			}
			scanner++;

		}
		// Point the second parameter string to the current counter
		paramStrings[2] = scanner;

		// Advance until the end of numbers
		while (*scanner >= '0' && *scanner <= '9') {
			scanner++;
		}

		// Scan to the end, replacing whitespace with null characters
		while (*scanner != '\0') {
			// If any incorrect characters while scanning (non space, newline, or tab) return 0 (syntax error)
			if (!checkValidChar(*scanner) || *scanner == '+' || *scanner == '-'
					|| *scanner == 'd' || isdigit(*scanner)) {
				return 0;
			}
			*scanner = '\0';
			scanner++;
		}
	}

	// Convert all paramStrings to the ints, and place them in the input integer array
	if (oneDie) {
		params[0] = 1;
	} else {
		params[0] = atoi(paramStrings[0]);
	}
	params[1] = atoi(paramStrings[1]);
	if (noAdd) {
		params[2] = 0;
	} else {
		params[2] = atoi(paramStrings[2]);
		if (isNeg) {
			params[2] = 0 - params[2];
		}
	}

	return 1;
}

int checkValidChar(char checkChar) {

// Because fuck regular expressions

// Check if integer, valid
	if (checkChar >= '0' && checkChar <= '9') {
		return 1;
	}
// Check for other characters
	switch (checkChar) {
		case 'd':
			return 1;
			break;
		case '+':
			return 1;
			break;
		case '-':
			return 1;
			break;
		case ' ':
			return 1;
			break;
		case '\t':
			return 1;
			break;
		case '\n':
			return 1;
			break;
	}
// Doesn't match the characters, return 0
	return 0;
}
