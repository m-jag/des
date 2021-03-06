#include <math.h>
#include "binary.h"
#include "des_tables.h"

int message_length = 0;

uint64_t d_mask = 0xFFFFFFF;
uint64_t cd = 0;

uint64_t initialKeyPermutation(uint64_t key)
{
	uint64_t pk = 0;

	uint8_t pos;
	for (int byte = 0; byte < 8; byte++)
	{
		for (int bit = 0; bit < 7; bit++)
		{
			pos = pc1[byte][bit];
			pk <<= 1;
			pk += ((key >> (64 - pos)) % 2);
			//printf("PC-1:%d Byte: %d Bit:%d Value:%d\n", pos, byte, bit, ((key >> (64 - pos)) % 2));
		}
	}
	printf("Key \t%s\n", addByteSeperators(buildBinaryString(key),  '-'));
	printf("PK \t%s\n", addByteSeperators(buildBinaryString(pk),  '-'));

	return pk;
}

// return pc2 applied to generate a round of the key (56 -> 48)
uint64_t applyPC2(uint64_t c_d)
{
	uint64_t subkey = 0;

	uint8_t pos;
	for (int byte = 0; byte < 8; byte++)
	{
		for (int bit = 0; bit < 6; bit++)
		{
			pos = pc2[byte][bit];
			subkey <<= 1;
			subkey += ((c_d >> (56 - pos)) % 2);
			//printf("PC-1:%d Byte: %d Bit:%d Value:%d\n", pos, byte, bit, ((c_d >> (56 - pos)) % 2));
		}
	}
	return subkey;
}

// shifts lower 28 bits by given amount and wraps upper bits
uint32_t shift(uint32_t val, int shift)
{
	val <<= shift;
	// msbs - most significant bits
	// grab the bits that need to be wrapped
	uint32_t msbs = val >> 28;
	val += msbs;
	val &= 0xFFFFFFF; //remove excess bits
	return val;	
}

uint64_t key_round(int round)
{
	uint32_t d = cd & d_mask;
	uint32_t c = ((cd & ~d_mask) >> 28) & d_mask;

	int shift_amt = round == 1 || round == 2 || round == 9 ||  round == 16 ? 1: 2;
	c = shift(c, shift_amt);
	d = shift(d, shift_amt);
	// Combine c and d (each are 28 bits)
	// Have to convert c to 64 bit integer before shift 
	// because otherwise it overflows and results in c = 0
	cd = ((uint64_t) c << 28) + d; 

	uint64_t round_key = applyPC2(cd);
	//printf("Round Key %d: \t%s\n", round, addByteSeperators(buildBinaryString(round_key),  '-'));
	
	//printf("C %d: \t%s\n", round, addByteSeperators(buildBinaryString(c),  '-'));
	
	//printf("D %d: \t%s\n", round, addByteSeperators(buildBinaryString(d),  '-'));

	return round_key;
}

void runDES(uint64_t key, char *message)
{
	printf("DES: Code in Development\n");
	uint64_t round_key = 0;
	cd = initialKeyPermutation(key);
	//printf("PK: %s\n", addByteSeperators(buildBinaryString(cd),  '-'));
	// get lower 28 bits and store in a 32 bit memory address
	for (int r = 1; r <= 16; r++)
	{
		//printf("Round %d\n", r);
		round_key = key_round(r);
		printf("Round %d Key: %s\n", r, addByteSeperators(buildBinaryString(round_key),  '-'));
		//printf("CD %d : %s\n", r, addByteSeperators(buildBinaryString(cd),  '-'));

	}
}

uint64_t grabBlock(char* message)
{
	uint64_t block = 0;
	for (int byte = 0; byte < 8; byte++)
	{
		if (*message)
		{
			block += *message;
			message++;
		}
		block << 8;
	}
	return block;
}

int main(int argc, char **argv)
{
	uint64_t key = stringToBin("0001001100110100010101110111100110011011101111001101111111110001");
	//uint64_t key = stringToBin("1110111011111111111111111111111111111111111111111111111111111111");
	//uint64_t key = stringToBin("1111111111111111111111111111111111111111111111111111111111111111");
	runDES(key, "Hello World!");
	//unsigned char keys[16][6];//[number of key rounds][size of key in bytes]
}