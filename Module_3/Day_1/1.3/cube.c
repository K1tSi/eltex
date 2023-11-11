#include <stdio.h>
int main(int argc, char* argv[]){
	double A;
	for(int i = 1; i < argc; i++){
	if(sscanf(argv[i],"%lf",&A))
		printf("%g ", A*A*A);
	}
	printf("\n");
	return 0;
}
