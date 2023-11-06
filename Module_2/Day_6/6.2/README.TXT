gcc -fPIC contact.c -c
gcc -fPIC list.c -c
gcc -shared list.o contact.o -o liblistcontact.so
gcc main.c -o program -L. -llistcontact
LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH
./program
