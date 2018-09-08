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
#include "sbox.h"

int main(void) {
	const char plaintext[] = "6bc1bee22e409f96e93d7e117393172a", *pos = plaintext; //0x7f78ae983109db901e27f3828fdcf0e5
	unsigned char *newState;
	unsigned char state[16];

	for (int count = 0; count < sizeof state/sizeof *state; count++) {
		sscanf(pos, "%2hhx", &state[count]);
		pos += 2;
	}

	newState = sBox(state);

	printf("0x");
	    for(int count = 0; count < 16; count++)
	        printf("%02x", newState[count]);
	printf("\n");

	return 0;
}



