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
#include "../include/keyschedule.h"
#include "../include/addroundkey.h"
#include "../include/mixcolumns.h"
#include "../include/subbytes.h"
#include "../include/shiftrows.h"
#include "../include/timing.h"

void printState(unsigned char state[16], char mes[]) {
	printf("%s: \t\t", mes);
	printf("0x");
	    for(int i = 0; i < 16; i++)
	        printf("%02x", state[i]);
	printf("\n");
}

void printHexChar(char ch) {
	printf("%x", ch & 0xff);
}

int main(void) {
	const char plaintext[] = "6bc1bee22e409f96e93d7e117393172a", keyString[] = "2b7e151628aed2a6abf7158809cf4f3c", *pos1 = plaintext, *pos2 = keyString;
	unsigned char state[16], key[16], tempState[16], tempKey[16], *newState, *newKey;

	startTimer();

	// Plaintext to state array and key similar
	for (int i = 0; i < sizeof state/sizeof *state; i++) {
		sscanf(pos1, "%2hhx", &tempState[i]);
		sscanf(pos2, "%2hhx", &tempKey[i]);
		pos1 += 2;
		pos2 += 2;
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			key[4 * i + j] = tempKey[4 * j + i];
			state[4 * i + j] = tempState[4 * j + i];
		}
	}

	//Key encryption
	newKey = keySchedule(key, 0);
	printState(newKey, "First key");
	for (int i = 1; i < 10; i++) {
		newKey = keySchedule(newKey, i);
		printState(newKey, "Next key");
	}

	printState(state, "Original state");

	newState = addRoundKey(state, key);
	printState(newState, "After AddRoundKey");

	newState = subBytes(newState);
	printState(newState, "After SubBytes");

	newState = shiftRows(newState);
	printState(newState, "After ShiftRows");

	newState = mixColumns(newState);
	printState(newState, "After MixColumns");

	newState = invMixColumns(newState);
	printState(newState, "After InvMixColumns");

	stopTimer();

	return 0;
}

//Key			2b7e151628aed2a6abf7158809cf4f3c
//Plaintext		6bc1bee22e409f96e93d7e117393172a
//Ciphertext	3ad77bb40d7a3660a89ecaf32466ef97
