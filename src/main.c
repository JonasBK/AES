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
#include "../include/timing.h"
#include "../include/AES128.h"

void printHexChar(char ch) {
	printf("%x", ch & 0xff);
}

int main(void) {
	const char plaintext[] = "54776F204F6E65204E696E652054776F", key[] = "5468617473206D79204B756E67204675";
	char *chipertext;

	printf("Key: \t\t%s\n", key);
	printf("Plaintext: \t%s\n", plaintext);

	startTimer();
	chipertext = AES128Encrypt(plaintext, key);
	stopTimer();

	printf("Chipertext: \t%s\n", chipertext);
	return 0;
}

//Key			00000000000000000000000000000000
//Plaintext		f34481ec3cc627bacd5dc3fb08f273e6
//Ciphertext	0336763e966d92595a567cc9ce537f5e

//Key			5468617473206D79204B756E67204675
//Plaintext		54776F204F6E65204E696E652054776F
//Chipertext	29c3505f571420f6402299b31a02d73a
