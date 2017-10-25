#ifndef BINARY
#define BINARY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>

char HLT[] = {'0', '1', '2', '3', '4', '5', '6', '7',
				'8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

//01010101 --> {'0', '1', '0', '1', '0', '1', '0', '1', '\0'}
char *byteToBinaryString(uint8_t byte, char *str)
{
	const int bits = 8;
	for(int b = bits - 1; b >=0; b--)
	{
		str[b] = byte%2 == 1? '1':'0';
		byte >>= 1;
	}
	str[bits] = '\0';

	return str;
}

//
char *byteToHexString(uint8_t byte)
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

uint64_t stringToBin(char *str)
{
	if (strlen(str) > 64)
	{
		printf("Binary value is larger than 64 bits.\n");
		return 0;
	}
	uint64_t binValue = 0;
	uint64_t weight = 1;
	for (int i = strlen(str) - 1; i >= 0; i--)
	{
		if (str[i]=='0' || str[i]=='1')
		{
			binValue += (str[i] - '0')* weight;
		}
		else
		{
			printf("Input contains non-binary values: %s\n", str);
			break;
		}
		weight = weight*2;
	}
	return binValue;
}

uint64_t stringToHex(char *str)
{
	if (strlen(str) > 8)
	{
		printf("Hex value is too large for an unsigned long value.\n");
		return 0;
	}
	uint64_t hexValue = 0;
	uint64_t weight = 1;
	for (int i = strlen(str) - 1; i >= 0; i--)
	{
		uint8_t digitValue = 0;
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


// For print values
char *buildString(uint64_t value)
{
	char *str = malloc(64 + 1);
	uint64_t lowest_byte_mask = stringToBin("11111111");
	int used_bytes = 0;
	for (int i = 7; i >= 0; i--)
	{
		uint8_t byte_value = (value >> i*8) & lowest_byte_mask;
		byteToBinaryString(byte_value, &str[(used_bytes++)*8]);
	}

	return str;
}


// For print values
char *addByteSeperators(char *str, char sep)
{
	char *str_sep = malloc(64 + 1 + 7);
	int num_sep = 0;
	for (int i = 0; i < 8; i++)
	{
		strncpy(&str_sep[i*8+i], &str[i*8], 8);
		str_sep[(i + 1)*8 + num_sep] = sep;
		num_sep++;
	}
	str_sep[64 + 7] = '\0';

	return str_sep;
}


#endif