cd ./fun
gcc -fPIC sum.c div.c pow2.c cos2.c mult.c arctg2.c -c
gcc -shared sum.o div.o pow2.o cos2.o mult.o arctg2.o -o libmath.so
LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH
cd ..
gcc main.c -o prog
./prog
