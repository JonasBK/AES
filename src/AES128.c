/*
 * AES128.c
 *
 *  Created on: Sep 9, 2018
 *      Author: jonas
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/keyschedule.h"
#include "../include/addroundkey.h"
#include "../include/mixcolumns.h"
#include "../include/subbytes.h"
#include "../include/shiftrows.h"

void printState(unsigned char state[16], char mes[]) {
	printf("%s: \t\t", mes);
	printf("0x");
	    for(int i = 0; i < 16; i++)
	        printf("%02x", state[i]);
	printf("\n");
}

char* AES128Encrypt(const char plaintext[16], const char keyString[16]) {
	static char res[32];
	int k = 0;
	const char *pos1 = plaintext, *pos2 = keyString;
	unsigned char state[16], key[16], tempState[16], tempKey[16], *newState, *newKey;

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

	newState = addRoundKey(state, key);
//	printState(newState, "newState");
	newKey = keySchedule(key, 0);

	for (int i = 1; i < 10; i++) {
		newState = subBytes(newState);
//		printState(newState, "After SubBytes");
		newState = shiftRows(newState);
//		printState(newState, "After ShiftRows");
		newState = mixColumns(newState);
//		printState(newState, "After MixColumns");
//		printState(newKey, "key");
		newState = addRoundKey(newState, newKey);
//		printState(newState, "After AddRoundKey");
		newKey = keySchedule(newKey, i);
//		printf("\n");
	}

	newState = subBytes(newState);
//	printState(newState, "After SubBytes");
	newState = shiftRows(newState);
//	printState(newState, "After ShiftRows");
//	printState(newKey, "key");
	newState = addRoundKey(newState, newKey);
//	printState(newState, "Final");

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			sprintf(&res[k], "%02x", newState[4 * j + i]);
			k += 2;
		}
	}
	return res;
}

