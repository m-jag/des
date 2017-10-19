#include "binary.h"

long byte1 = 126;

int main(int argc, char *argv[])
{
	char *bin1 = byteToBinaryString(byte1);
	char *hex1 = byteToHexString(byte1);
	printf("Values\n");
	printf("Decimal: %d\n", byte1);
	printf("Binary: %s\n", bin1);
	printf("Hex: 0x%s\n", hex1);
	free(bin1);
	free(hex1);
}