#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void coming(Queue* q){
    if(random()%1000000 < 210000){       // 21% вероятность прихода 
        insert(q, random(), 1+random()%255);
    }
}
void out(Queue* q){
    if(random()%1000000 > 710000){        // 29% вероятность попытки извлечения
        if (random()%100 > 66)             // 33% каждый вид извлечения
            getInformation(q, 1 + random()%255);
        else if (random()%100 < 50)
            getInformation(q, -1 - random()%255);
        else 
            getInformation(q, 0);
    }
}
int main(){
    Queue* queue = createQueue();
    srand(time(NULL));
    //insert(queue, 32413243, 100);
    printQueue(queue);
    int i = 0;
    while(i < 100000){
        coming(queue);
        i++;
        out(queue);
    }
    printQueue(queue);

    return 0;
}