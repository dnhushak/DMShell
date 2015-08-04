#ifndef DICEROLLER_H_
#define DICEROLLER_H_

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

void initRoller();

int generateRandom(int min, int max);

int rollDie(int dieSize);

int rollDice(int numDice, int diceSize, int additive, int verbose);

int rollDiceCommand(char* rollString, int verbose);

int parseRoll(char* rollString, int * params);

int checkValidChar(char checkChar);

#endif /* DICEROLLER_H_ */
