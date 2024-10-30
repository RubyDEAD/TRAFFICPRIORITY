#include <stdio.h>
#include <stdlib.h>
#define MAX 8


typedef enum{
    MainLane, DiversionLane, Left_MainLane, Right_MainLane, Left_DiversionLane, Right_DiversionLane, Pedestrian_MainLane, Pedestrian_DiversionLane
}LaneType;


typedef struct {
    LaneType laneName;
    float time;
}Lane;


typedef struct{
    Lane lanes[MAX];
    int size;
}PQueue;

Lane createLane(LaneType L, float time);
void initPQueue(PQueue *q);
void enqueue(PQueue *q, Lane L);
Lane dequeue(PQueue *q);
Lane peek(PQueue q);
void saveFile(const char*, PQueue q);
void getData(const char*, PQueue *q);
void displayLane(PQueue q);
float calTime(PQueue q);




int main()
{
    PQueue q;
    initPQueue(&q);
    // enqueue(&q, createLane(0, 15.23));
    // enqueue(&q, createLane(3, 20.39));
    // enqueue(&q, createLane(1, 50.11));
    // enqueue(&q, createLane(4, 17.57));
    // enqueue(&q, createLane(5, 33.10));
    // enqueue(&q, createLane(6, 59.23));
    // enqueue(&q, createLane(7, 41.44));
    // saveFile("traffic.dat", q);
    getData("traffic.dat", &q);
    displayLane(q);
    printf("OVerall Time: %.2fs", calTime(q));




    return 0;
}
Lane createLane(LaneType L, float time){
    Lane x;
    x.laneName = L;
    x.time = time;

    return x;
}
void initPQueue(PQueue *q){
    q->size = 0;
}
void enqueue(PQueue *q, Lane L)
{
    if(q->size >= MAX){
        exit;
    }

    q->lanes[q->size] = L;
    int child = q->size;
    int parent = (child - 1) / 2;
    q->size++;


    while(child > 0 && q->lanes[child].laneName < q->lanes[parent].laneName){
        Lane temp;
        temp = q->lanes[child];
        q->lanes[child] = q->lanes[parent];
        q->lanes[parent] = temp;
        child = parent;
        parent = (child - 1) / 2;
    }



}
Lane dequeue(PQueue *q){

}
Lane peek(PQueue q){
    return q.lanes[0];
}
void saveFile(const char* filename, PQueue q)
{
    FILE *fp = fopen(filename, "wb");
    if(fp){
        fwrite(&q, sizeof(PQueue), 1, fp);
    }
    fclose(fp);
}
void getData(const char* filename, PQueue *q)
{
    FILE *fp = fopen(filename, "rb");
    if(fp){
        fread(q, sizeof(PQueue), 1, fp);
    }
    fclose(fp);

}
void displayLane(PQueue q)
{
    int i;
    for(i = 0; i < q.size; ++i){
        switch(q.lanes[i].laneName){
            case MainLane:
                printf("Main Lane\n");
                printf("Time: %.2fs\n", q.lanes[i].time);
            break;

            case DiversionLane:
                printf("Diversion Lane\n");
                printf("Time: %.2fs\n", q.lanes[i].time);
            break;

            case Left_MainLane:
                printf("Left Main Lane\n");
                printf("Time: %.2fs\n", q.lanes[i].time);
            break;

            case Right_MainLane:
                printf("Right Main Lane\n");
                printf("Time: %.2fs\n", q.lanes[i].time);
            break;

            case Left_DiversionLane:
                printf("Left Diversion Lane\n");
                printf("Time: %.2fs\n", q.lanes[i].time);
            break;

            case Right_DiversionLane:
                printf("Right Diversion Lane\n");
                printf("Time: %.2fs\n", q.lanes[i].time);
            break;
            
            case Pedestrian_MainLane:
                printf("Pedestrian Main Lane\n");
                printf("Time: %.2fs\n", q.lanes[i].time);
            break;

            case Pedestrian_DiversionLane:
                printf("Pedestrian Diversion Lane\n");
                printf("Time: %.2fs\n", q.lanes[i].time);
            break;

            default:
            printf("No Lane Assigned\n");
            break;
        }
    }
}
float calTime(PQueue q){
    int i;
    float time = 0;
    for(i = 0; i < q.size; ++i){
        time += q.lanes[i].time;
    }
    return time;
}



