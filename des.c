#include <math.h>
#include "binary.h"
#include "des_tables.h"


uint64_t d_mask = 0xFFFFFFF;

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
	return cd;
}

uint32_t shift(uint32_t val, int shift)
{
	uint32_t msb = (val >> 27) % 2;
	val <<= shift;
	val += msb;
	val &= 0xFFFFFFF; //remove excess bits
	return val;	
}

uint64_t keyRound(int round, uint32_t c, uint32_t d)
{
	int shift = round == 1 || round == 2 | round == 9 |  round == 16 ? 1: 2;
	c = shift(c);
	d = shift(d);
	uint64_t cd = (c << 28) + d;
	return applyPC2(cd);
}

void runDES(uint64_t key, char *message)
{
	printf("DES: Code in Development\n");
	uint64_t pk = initialKeyPermutation(key);
	printf("PK: %s\n", addByteSeperators(buildString(pk),  '-'));
	// get lower 28 bits and store in a 32 bit memory address
	uint32_t d = pk & d_mask;
	uint32_t c = ((pk & ~d_mask) >> 28) & d_mask;
	printf("C: %s\n", addByteSeperators(buildString(c),  '-'));
	printf("D: %s\n", addByteSeperators(buildString(d),  '-'));
	for (int r = 1; r <= 16; r++)
	{
		keyRound(c, d);
	}
}

int main(int argc, char **argv)
{
	uint64_t key = stringToBin("0001001100110100010101110111100110011011101111001101111111110001");
	//uint64_t key = stringToBin("1111111111111111111111111111111111111111111111111111111111111111");
	runDES(key, "Hello World!");
	//unsigned char keys[16][6];//[number of key rounds][size of key in bytes]
}