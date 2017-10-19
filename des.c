#include <math.h>
#include "binary.h"
#include "des_tables.h"

bool verbose = false;

unsigned char key[8] = { 255, 255, 255, 255, 255, 255, 255, 255};

// return pc1 applied to the key
void initialKeyPermutation(unsigned char pk[])
{
	printf(" - Initial Key Permutation - \n");
	printf("%s %s %s %s %s %s %s %s\n", byteToBinaryString(pk[0]), byteToBinaryString(pk[1]),
										byteToBinaryString(pk[2]), byteToBinaryString(pk[3]),
										byteToBinaryString(pk[4]), byteToBinaryString(pk[5]),
										byteToBinaryString(pk[6]), byteToBinaryString(pk[7]));
	printf("- Under Construction -\n");
	unsigned char weight;
	unsigned char permutatedVal;
	for (int byte = 0; byte < sizeof(key); byte++)
	{
		weight = 1;
		for (int bit = 6; bit >= 0; bit--)
		{
			permutatedVal = pc1[byte][bit] - 1;
			//printf("PK = %lu\n", pk[byte]);
			//printf("PC-1: %d\n", permutatedVal + 1);
			pk[byte] += getbit(key[(permutatedVal)/8], permutatedVal%8) * weight;
			//printf("key[%d][%d] : %d\n", permutatedVal/8, permutatedVal%8, getbit(key[(permutatedVal)/8], permutatedVal%8));
			//printf("weight: %d\n", weight);
			weight *= 2;
			printf("%s %s %s %s %s %s %s %s\n", byteToBinaryString(pk[0]), byteToBinaryString(pk[1]),
										byteToBinaryString(pk[2]), byteToBinaryString(pk[3]),
										byteToBinaryString(pk[4]), byteToBinaryString(pk[5]),
										byteToBinaryString(pk[6]), byteToBinaryString(pk[7]));
		}

	}

	printf("- Permuted Key - \n");
	printf("%s %s %s %s %s %s %s %s\n", byteToBinaryString(pk[0]), byteToBinaryString(pk[1]),
										byteToBinaryString(pk[2]), byteToBinaryString(pk[3]),
										byteToBinaryString(pk[4]), byteToBinaryString(pk[5]),
										byteToBinaryString(pk[6]), byteToBinaryString(pk[7]));
}

int main(int argc, char *argv[])
{
	printf("DES: Code in Development\n");
	unsigned char pk[8] = {0,0,0,0,0,0,0,0};
	initialKeyPermutation(pk);
}