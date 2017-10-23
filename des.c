#include <math.h>
#include "binary.h"
#include "des_tables.h"

void initialKeyPermutation(unsigned char *pk, unsigned char *key)
{
	unsigned char weight;
	unsigned char permutatedVal;
	for (int byte = 0; byte < 8; byte++) // limit to first byte for testing
	{
		weight = 1;
		for (int bit = 6; bit >= 0; bit--)
		{
			permutatedVal = pc1[byte][bit] - 1;
			pk[byte] += getbit(key[(permutatedVal)/8], permutatedVal%8) * weight;
			weight *= 2;
		}
	}
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
		c[b] << rotate;
		c[b] & 127; //127 base 10 = 0111 1111 base 2 sets the unused msb to 0
		
	}
}

void runDES(unsigned char *key, char *message)
{
	printf("DES: Code in Development\n");
	unsigned char pk[8] = {0,0,0,0,0,0,0,0};
	initialKeyPermutation(pk, key);
	unsigned char c[4] = {pk[0], pk[1], pk[2], pk[3]};
	unsigned char d[4] = {pk[4], pk[5], pk[6], pk[7]};
	for (int r = 1; r <= 16; r++)
	{
		//keyRound()
	}
}

int main(int argc, char **argv)
{
	runDES(key, "Hello World!");
	//unsigned char keys[16][6];//[number of key rounds][size of key in bytes]
}