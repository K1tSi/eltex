#include <stdio.h>
int main(int argc, char* argv[]){
	double sum = 0;
	double A;
	for(int i = 1; i < argc; i++){
	if(sscanf(argv[i],"%lf",&A))
		sum += A;
	}
	printf("%g\n", sum);
	return 0;
}
