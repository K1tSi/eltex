gcc contact.c -c
gcc list.c -c
ar rc liblistcontact.a list.o contact.o
gcc main.c -o program -L. -llistcontact
