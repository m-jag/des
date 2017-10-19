#include "binary.h"
//MPI CC script around MPI to find mpi.h
//DLL collection of code you can embed in another program
//mpirun to execute mpi programs (to get the dlls)
//bsub -n 4 -R "span[ptile=1]" -o %J.txt "/opt/ibm/platform_mpi/bin/mpirun -lsf -vapi /home/mjagodzinski3154/helloworld_mpi"

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