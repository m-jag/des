#include <math.h>
#include "binary.h"
#include "des_tables.h"

#define NONE 0
#define LEVEL_ONE 1
#define LEVEL_TWO 2

int verbose = LEVEL_ONE;
bool visualIKP = false;

unsigned char key[8] = { 187, 65, 4, 37, 207, 54, 120, 255};

// return pc1 applied to the key
void initialKeyPermutation(unsigned char pk[])
{
	if (verbose >= LEVEL_ONE && visualIKP)
	{
		printf(" ---- Initial Key Permutationa ---- \n");
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
	for (int byte = 0; byte < sizeof(key); byte++) // limit to first byte for testing
	{
		weight = 1;
		for (int bit = 6; bit >= 0; bit--)
		{
			permutatedVal = pc1[byte][bit] - 1;
			if (verbose >= LEVEL_TWO  && visualIKP)
			{
				printf("----------\n");
				printf("PC-1 : %d\n", permutatedVal + 1);
				printf(" - Key - \n");
				printf("       8        16       24       32       40       48       56       64\n");
				printf("%s %s %s %s %s %s %s %s\n", byteToBinaryString(key[0]), byteToBinaryString(key[1]),
													byteToBinaryString(key[2]), byteToBinaryString(key[3]),
													byteToBinaryString(key[4]), byteToBinaryString(key[5]),
													byteToBinaryString(key[6]), byteToBinaryString(key[7]));
				//Key Pointer
				for (int i = 0; i < permutatedVal; i++)
				{
					i%8==7? printf("  "): printf(" ");
				}
				printf("|\n");
				
				//printf("Key Position: %d\n", permutatedVal);
				//printf("Permutated Position: %d\n", byte*8 + bit + 1);

				int lowValue = permutatedVal < byte*8 + bit + 1? permutatedVal: byte*8 + bit + 1; //implementation of min
				int highValue = permutatedVal > byte*8 + bit + 1? permutatedVal: byte*8 + bit + 1; //implementation of max

				for (int i = 0; i < lowValue; i++)
				{
					printf(" ");
					if (i%8==7)
						printf(" ");
				}
				
				bool extra_space;
				if (highValue != lowValue)
				{
					printf("+");
					extra_space = lowValue%8==7;
					for (int i = lowValue + 1; i < highValue; i++)
					{
						if (extra_space && i%8==0)
							printf("-");
						printf("-");
						extra_space = i%8==7;
					}
					if (highValue%8==0)
						printf("-");
				}
				printf("+\n");
				
				extra_space = false;
				for (int i = 0; i < byte*8 + bit + 1; i++)
				{
					if (extra_space && i%8==0)
						printf(" ");
					printf(" ");
					extra_space = i%8==7;
				}
				if ((bit + 1)%8==0)
					printf(" ");
				printf("|\n");
				//For Debugging: printf("PK = %lu\n", pk[byte]);
				//For Debugging: printf("key[%d][%d] : %d\n", permutatedVal/8, permutatedVal%8, getbit(key[(permutatedVal)/8], permutatedVal%8));
				//For Debugging: printf("weight: %d\n", weight);
			}
			pk[byte] += getbit(key[(permutatedVal)/8], permutatedVal%8) * weight;
			weight *= 2;
			if (verbose >= LEVEL_TWO  && visualIKP)
			{
				printf("%s %s %s %s %s %s %s %s\n", byteToBinaryString(pk[0]), byteToBinaryString(pk[1]),
										byteToBinaryString(pk[2]), byteToBinaryString(pk[3]),
										byteToBinaryString(pk[4]), byteToBinaryString(pk[5]),
										byteToBinaryString(pk[6]), byteToBinaryString(pk[7]));
			}
		}
		if (verbose == LEVEL_ONE  && visualIKP)
		{
			printf("%s %s %s %s %s %s %s %s\n", byteToBinaryString(pk[0]), byteToBinaryString(pk[1]),
												byteToBinaryString(pk[2]), byteToBinaryString(pk[3]),
												byteToBinaryString(pk[4]), byteToBinaryString(pk[5]),
												byteToBinaryString(pk[6]), byteToBinaryString(pk[7]));
		}
		else if (verbose == LEVEL_TWO  && visualIKP)
		{
			printf("---------\n");
		}
	}
	if (verbose >= LEVEL_ONE  && visualIKP)
	{
		printf("- Permuted Key - \n");
		printf("%s %s %s %s %s %s %s %s\n", byteToBinaryString(pk[0]), byteToBinaryString(pk[1]),
										byteToBinaryString(pk[2]), byteToBinaryString(pk[3]),
										byteToBinaryString(pk[4]), byteToBinaryString(pk[5]),
										byteToBinaryString(pk[6]), byteToBinaryString(pk[7]));
		printf(" ---------------------------------- \n");
	}
}

void applyPC2(unsigned char [], unsigned char [])

void keyRounds(unsigned char keys[][])
{

}



int main(int argc, char *argv[])
{
	printf("DES: Code in Development\n");
	unsigned char pk[8] = {0,0,0,0,0,0,0,0};
	initialKeyPermutation(pk);
	unsigned char keys[16][];//[number of key rounds][size of key in bytes]
}