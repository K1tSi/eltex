#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#define CHANCE_COMING 14
#define CHANCE_OUT 29
void coming(Queue* q){
    if(random()%1000000 < 10000*CHANCE_COMING){       // 14% вероятность прихода 
        insert(q, random(), 1+random()%255);
    }
}
void out(Queue* q){
    if(random()%1000000 > (1000000-CHANCE_OUT*10000)){        // 29% вероятность попытки извлечения
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
    printf("\n");
    int i = 0, maxq = 0;
    while(i < 100000){
        coming(queue);
        i++;
        out(queue);
        if (queue->size > maxq) maxq = queue->size; 
    }
    printQueue(queue);
    printf("Max len queue: %d\n", maxq);
    return 0;
}