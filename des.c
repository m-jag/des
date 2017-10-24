#include <math.h>
#include "binary.h"
#include "des_tables.h"

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
			printf("PC-1:%d Byte: %d Bit:%d Value:%d\n", permutatedVal+1, byte, bit, getbit(key, permutatedVal));
			weight *= 2;
		}
	}

	return pk;
}

// return pc2 applied to generate a round of the key (56 -> 48)
void applyPC2(unsigned char key[static 8])
{

}

void keyRound(int round, unsigned char c[static 4], unsigned char d[static 4], unsigned char outKey[static 8])
{
	int rotate = round == 1 || round == 2 | round == 9 |  round == 16 ? 1: 2;
	//unsigned char temp = c[0];
	for (int b = 0; b < 4; b++)
	{	
	}
}

void runDES(uint64_t key, char *message)
{
	printf("DES: Code in Development\n");
	uint64_t pk = initialKeyPermutation(key);
	for (int r = 1; r <= 16; r++)
	{
		//keyRound()
	}
}

int main(int argc, char **argv)
{
	uint64_t key = stringToBin("0001001100110100010101110111100110011011101111001101111111110001");
	//uint64_t key = stringToBin("1111111111111111111111111111111111111111111111111111111111111111");
	//runDES(key, "Hello World!");
	uint64_t pk = initialKeyPermutation(key);
	char *str = addByteSeperators(buildString(key),  '-');
	printf("key: %s\n", str);
	str = addByteSeperators(buildString(pk),  '-');
	printf("permutated key: %s\n", str);
	free(str);
	//unsigned char keys[16][6];//[number of key rounds][size of key in bytes]
}