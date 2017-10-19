#include <math.h>
#include "binary.h"
#include "des_tables.h"

#define NONE 0
#define LEVEL_ONE 1
#define LEVEL_TWO 2

int verbose = LEVEL_TWO;

unsigned char key[8] = { 255, 255, 255, 255, 255, 255, 255, 255};

// return pc1 applied to the key
void initialKeyPermutation(unsigned char pk[])
{
	if (verbose >= LEVEL_ONE)
	{
		printf(" - Key - \n");
		printf("%s %s %s %s %s %s %s %s\n", byteToBinaryString(key[0]), byteToBinaryString(key[1]),
										byteToBinaryString(key[2]), byteToBinaryString(key[3]),
										byteToBinaryString(key[4]), byteToBinaryString(key[5]),
										byteToBinaryString(key[6]), byteToBinaryString(key[7]));
		printf(" - Initial Key Permutation - \n");
		printf("%s %s %s %s %s %s %s %s\n", byteToBinaryString(pk[0]), byteToBinaryString(pk[1]),
										byteToBinaryString(pk[2]), byteToBinaryString(pk[3]),
										byteToBinaryString(pk[4]), byteToBinaryString(pk[5]),
										byteToBinaryString(pk[6]), byteToBinaryString(pk[7]));
		printf("- Permutation -\n");
	}
	unsigned char weight;
	unsigned char permutatedVal;
	for (int byte = 0; byte < sizeof(key); byte++)
	{
		weight = 1;
		for (int bit = 6; bit >= 0; bit--)
		{
			permutatedVal = pc1[byte][bit] - 1;
			if (verbose >= LEVEL_TWO)
			{
				printf("----------\n");
				printf("PC-1 : %d\n", permutatedVal + 1);
				printf(" - Key - \n");
				printf("       8        16       24       32       40       48       56       64\n");
				printf("%s %s %s %s %s %s %s %s\n", byteToBinaryString(key[0]), byteToBinaryString(key[1]),
										byteToBinaryString(key[2]), byteToBinaryString(key[3]),
										byteToBinaryString(key[4]), byteToBinaryString(key[5]),
										byteToBinaryString(key[6]), byteToBinaryString(key[7]));
				for (int i = 0; i < permutatedVal; i++)
				{
					i%8==7? printf("  "): printf(" ");
				}
				printf("|\n");
				int counter = 0;
				for (int i = 0; i < byte*8 + bit; i++)
				{
					i%8==7 ? printf("  "): printf(" ");
				}
				printf("+\n");
				//For Debugging: printf("PK = %lu\n", pk[byte]);
				//For Debugging: printf("key[%d][%d] : %d\n", permutatedVal/8, permutatedVal%8, getbit(key[(permutatedVal)/8], permutatedVal%8));
				//For Debugging: printf("weight: %d\n", weight);
			}
			pk[byte] += getbit(key[(permutatedVal)/8], permutatedVal%8) * weight;
			weight *= 2;
		}
		if (verbose >= LEVEL_ONE)
		{
			printf("%s %s %s %s %s %s %s %s\n", byteToBinaryString(pk[0]), byteToBinaryString(pk[1]),
												byteToBinaryString(pk[2]), byteToBinaryString(pk[3]),
												byteToBinaryString(pk[4]), byteToBinaryString(pk[5]),
												byteToBinaryString(pk[6]), byteToBinaryString(pk[7]));
		}
	}
	if (verbose >= LEVEL_ONE)
	{
		printf("- Permuted Key - \n");
		printf("%s %s %s %s %s %s %s %s\n", byteToBinaryString(pk[0]), byteToBinaryString(pk[1]),
										byteToBinaryString(pk[2]), byteToBinaryString(pk[3]),
										byteToBinaryString(pk[4]), byteToBinaryString(pk[5]),
										byteToBinaryString(pk[6]), byteToBinaryString(pk[7]));
	}
}

int main(int argc, char *argv[])
{
	printf("DES: Code in Development\n");
	unsigned char pk[8] = {0,0,0,0,0,0,0,0};
	initialKeyPermutation(pk);
}