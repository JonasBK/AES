/*
 ============================================================================
 Name        : main.c
 Author      : Jonas
 Version     :
 Copyright   : 
 Description : AES implementation
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/mixcolumns.h"
#include "../include/subbytes.h"
#include "../include/timing.h"

void printState(unsigned char state[16]) {
	printf("0x");
	    for(int i = 0; i < 16; i++)
	        printf("%02x", state[i]);
	printf("\n");
}

void printHexChar(char ch) {
	printf("%x", ch & 0xff);
}

int main(void) {
	const char plaintext[] = "6bc1bee22e409f96e93d7e117393172a", *pos = plaintext;
	unsigned char state[16], *newState;

	startTimer();

	// Plaintext to state array {x1, x2, x3, ...}
	for (int i = 0; i < sizeof state/sizeof *state; i++) {
		sscanf(pos, "%2hhx", &state[i]);
		pos += 2;
	}
	printState(state);

	newState = subBytes(state);
	printState(newState);

	newState = mixColumns(newState);
	printState(newState);

	newState = invMixColumns(newState);
	printState(newState);

	stopTimer();

	return 0;
}

//0x6bc1bee22e409f96e93d7e117393172a
//0x7f78ae983109db901e27f3828fdcf0e5
//0x3c1032e7b0dffddbf8408323ab053a70
