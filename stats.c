#include "stats.h"
#include "diceRoller.h"

int calculateModifier(int stat) {
	return (stat - 10) / 2;
}

int rollStat(int verbose) {
	int stat = 0;
	int min = 7;
	int rollValue = 0;
	int i;
	if (verbose) {
		printf(KRED "\nRolling stat...\n");
		printf(KBLU "====================\n");
	}
	for (i = 0; i < 4; i++) {
		rollValue = rollDie(6);
		if (verbose) {
			// Print individual roll values if verbose
			printf(KCYN "d6 Roll %d: \t%d\n", i + 1, rollValue);
		}
		if (rollValue < min) {
			min = rollValue;
		}
		stat += rollValue;

	}
	// Remove lowest die roll
	stat -= min;
	if (verbose) {
		// Print minimum
		printf(KGRN "Minimum Roll: \t%d\n", min);
	}
	if (verbose) {
		printf(KBLU "====================\n");
	}
	printf(KRED "4d6-lowest Result:" KYEL "\t%d" KNRM "\n\n", stat);
	return stat;
}

int * rollStats(int verbose) {
	int stats[6];
	int i = 0;
	for (i = 0; i<6; i++){
		stats[i] = rollStat(verbose);
	}
	return stats;
}
