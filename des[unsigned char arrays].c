#include <math.h>
#include "binary[unsigned char].h"
#include "des_tables.h"

#define NONE 0
#define LEVEL_ONE 1
#define LEVEL_TWO 2

typedef unsigned char EightBytes[8];

int verbose = LEVEL_ONE;
bool visualIKP = true;

// return pc1 applied to the key (64->56)
// key stored as 8 bytes
// permuted key stored as 8 bytes (sets of 7) with the highest order bits being unused and set to 0
void initialKeyPermutation(EightBytes pk, EightBytes key)
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
	for (int byte = 0; byte < 8; byte++) // limit to first byte for testing
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

// return pc2 applied to generate a round of the key (56 -> 48)
void applyPC2(unsigned char key[static 8])
{

}

void keyRound(int round, unsigned char c[static 4], unsigned char c[static 4], unsigned char outKey[static 8])
{
	int rotate = round == 1 || round == 2 | round == 9 |  round == 16 ? 1: 2;
	unsigned char temp = c[0]
	for (int b = 0; b < 4; b++)
	{
		c[b] << rotate;
		c[b] & 127; //127 base 10 = 0111 1111 base 2 sets the unused msb to 0
		
	}
}

void runDES(EightBytes key, char *message)
{
	printf("DES: Code in Development\n");
	EightBytes pk = {0,0,0,0,0,0,0,0};
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
	EightBytes key = {255,255,255,255,255,255,255,255};//{ 187, 65, 4, 37, 207, 54, 120, 255};
	runDES(key, "Hello World!");
	//unsigned char keys[16][6];//[number of key rounds][size of key in bytes]
}