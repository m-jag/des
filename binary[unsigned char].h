#ifndef BINARY
#define BINARY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char HLT[] = {'0', '1', '2', '3', '4', '5', '6', '7',
				'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

unsigned char getbit(unsigned char byte, int pos)
{
	if (pos >= 8)
	{
		return -1;
	}
	return (byte >> pos) % 2;
}

//01010101 --> {'0', '1', '0', '1', '0', '1', '0', '1', '\0'}
char *byteToBinaryString(unsigned char byte)
{
	const int bits = 8;
	char *str = malloc(bits+1);
	for(int b = bits - 1; b >=0; b--)
	{
		str[b] = byte%2 == 1? '1':'0';
		byte >>= 1;
	}
	str[bits] = '\0';

	return str;
}

//
char *byteToHexString(unsigned char byte)
{
	int hexChars = 2;
	char *str = malloc(hexChars + 1);
	for(int b = hexChars - 1; b >=0; b--)
	{
		str[b]=HLT[byte%16];
		byte >>= 4;
	}
	str[hexChars] = '\0';

	return str;
}

unsigned char stringToBin(char *str)
{
	if (strlen(str) > 8)
	{
		printf("Binary value is too large for an unsigned long value.\n");
		return 0;
	}
	unsigned long binValue = 0;
	unsigned long weight = 1;
	for (int i = strlen(str) - 1; i >= 0; i--)
	{
		if (isdigit(str[i]))
		{
			binValue += (str[i] - '0')* weight;
		}
		else
		{
			printf("Input contains non-numeric values: %s\n", str);
			break;
		}
		weight = weight*2;
	}
	return binValue;
}

unsigned char stringToHex(char *str)
{
	if (strlen(str) > 2)
	{
		printf("Hex value is too large for an unsigned long value.\n");
		return 0;
	}
	unsigned long hexValue = 0;
	unsigned long weight = 1;
	for (int i = strlen(str) - 1; i >= 0; i--)
	{
		int digitValue = 0;
		bool unknownValue = false;
		switch(str[i])
		{
			case '0': digitValue = 0; break;
			case '1': digitValue = 1; break;
			case '2': digitValue = 2; break;
			case '3': digitValue = 3; break;
			case '4': digitValue = 4; break;
			case '5': digitValue = 5; break;
			case '6': digitValue = 6; break;
			case '7': digitValue = 7; break;
			case '8': digitValue = 8; break;
			case '9': digitValue = 9; break;
			case 'A': digitValue = 10; break;
			case 'B': digitValue = 11; break;
			case 'C': digitValue = 12; break;
			case 'D': digitValue = 13; break;
			case 'E': digitValue = 14; break;
			case 'F': digitValue = 15; break;
			default: unknownValue = true; break;
		}
		if (unknownValue)
		{
			printf("Input contains non-numeric values: %s\n", str); 
		}
		hexValue += digitValue * weight;
		weight = weight*16;
	}
	return hexValue;
}
#endif