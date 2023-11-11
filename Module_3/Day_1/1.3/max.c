#include <stdio.h>
int main(int argc, char* argv[]){
	double max = 0;
	double A;
	for(int i = 1; i < argc; i++){
	if(sscanf(argv[i],"%lf",&A))
		if(A>max) max = A;
	}
	printf("%g\n", max);
	return 0;
}
