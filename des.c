#include <math.h>
#include "binary.h"
#include "des_tables.h"


uint64_t d_mask = 0xFFFFFFF;
uint64_t cd = 0;

uint64_t initialKeyPermutation(uint64_t key)
{
	uint64_t pk = 0;

	uint64_t weight = 1;
	uint8_t permutatedVal;
	for (int byte = 7; byte >= 0; byte--)
	{
		for (int bit = 6; bit >= 0; bit--)
		{
			permutatedVal = pc1[byte][bit] - 1;
			pk += getbit(key, permutatedVal) * weight;
			//printf("PC-1:%d Byte: %d Bit:%d Value:%d\n", permutatedVal+1, byte, bit, getbit(key, permutatedVal));
			weight *= 2;
		}
	}

	return pk;
}

// return pc2 applied to generate a round of the key (56 -> 48)
uint64_t applyPC2(uint64_t cd)
{
	uint64_t subkey = 0;
	uint64_t weight = 1;
	uint8_t permutatedVal;
	for (int byte = 7; byte >= 0; byte--)
	{
		for (int bit = 5; bit >= 0; bit--)
		{
			permutatedVal = pc2[byte][bit] - 1;
			cd += getbit(cd, permutatedVal) * weight;
			//printf("PC-1:%d Byte: %d Bit:%d Value:%d\n", permutatedVal+1, byte, bit, getbit(key, permutatedVal));
			weight *= 2;
		}
	}
	return cd;
}

// shifts lower 28 bits by given amount and wraps upper bits
uint32_t shift(uint32_t val, int shift)
{
	val <<= shift;
	// msbs - most significant bits
	// grab the bits that need to be wrapped
	uint32_t msbs = (val >> 28) % 2;
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
	cd = ((uint64_t) c << 28) + d; // Combine c and d
	//printf("Round Key %d: \t%s\n", round, addByteSeperators(buildString(round_key),  '-'));
	
	printf("C %d: \t%s\n", round, addByteSeperators(buildString(c),  '-'));
	
	printf("D %d: \t%s\n", round, addByteSeperators(buildString(d),  '-'));
	

	uint64_t round_key = applyPC2(cd);
	return round_key;
}

void runDES(uint64_t key, char *message)
{
	printf("DES: Code in Development\n");

	uint64_t round_key = 0;
	cd = initialKeyPermutation(key);
	printf("PK: %s\n", addByteSeperators(buildString(cd),  '-'));
	// get lower 28 bits and store in a 32 bit memory address
	for (int r = 1; r <= 16; r++)
	{
		//printf("Round %d\n", r);
		round_key = key_round(r);
	}
}

int main(int argc, char **argv)
{
	uint64_t key = stringToBin("0001001100110100010101110111100110011011101111001101111111110001");
	//uint64_t key = stringToBin("1111111111111111111111111111111111111111111111111111111111111111");
	runDES(key, "Hello World!");
	//unsigned char keys[16][6];//[number of key rounds][size of key in bytes]
}