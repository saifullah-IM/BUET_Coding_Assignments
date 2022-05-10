#include<iostream>
#include<cstdio>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#include<cstring>
#include<time.h>
#include<atomic>

using namespace std;

#define number_of_cyclists 10
#define number_of_servicemen 3
#define payment_room_capacity 2

sem_t empty_payment_room;
pthread_mutex_t mutex[number_of_servicemen];
pthread_cond_t cond;
atomic<int> to_depart(0);

void* get_service(void* arg){
    int id = *(int*)arg;
    for (int current_serviceman = 1; current_serviceman <= number_of_servicemen; current_serviceman++) {
        pthread_mutex_lock(&mutex[current_serviceman-1]);
        if (current_serviceman == 1) {
            while(to_depart > 0) pthread_cond_wait(&cond, &mutex[0]);
        }
        else pthread_mutex_unlock(&mutex[current_serviceman-2]);
        printf("%d started taking service from serviceman %d\n",id,current_serviceman);
        int service_time = rand() % 10 + 1;
        sleep(service_time);
        printf("%d finished taking service from serviceman %d\n",id,current_serviceman);
    }
    pthread_mutex_unlock(&mutex[number_of_servicemen-1]);
    //pthread_exit((void*)strcat((char*)arg," consumer is finishing\n"));

    sem_wait(&empty_payment_room);
    printf("%d started paying the service bill\n",id);
    int payment_time = rand() % 10 + 1;
    sleep(payment_time);
    printf("%d finished paying the service bill\n",id);
    // pthread_mutex_lock(&mutex_payment);
    // in_payment_room++;
    // pthread_mutex_unlock(&mutex_payment);
    sem_post(&empty_payment_room);

    to_depart += 1;
    for (int i = 0; i < number_of_servicemen; i++) {
        pthread_mutex_lock(&mutex[i]);
    }
    to_depart -= 1;
    int departure_time = rand() % 10 + 1;
    sleep(departure_time);
    printf("%d has departed\n",id);
    pthread_cond_broadcast(&cond);
    for (int i = 0; i < number_of_servicemen; i++) {
        pthread_mutex_unlock(&mutex[i]);
    }
}

int main(int argc, char* argv[])
{
    int res;

    // initializing payment room
    res = sem_init(&empty_payment_room,0,payment_room_capacity);
    if(res != 0){
        printf("Failed\n");
    } 


    // initializing conditional variable
    res = pthread_cond_init(&cond,NULL);
    if(res != 0){
        printf("Failed\n");
    }


    // initializing servicemen mutex
    for (int i = 0; i < number_of_servicemen; i++) {
        res = pthread_mutex_init(&mutex[i],NULL);
        if(res != 0){
            printf("Failed\n");
        }
    }


    // creating cyclists threads
    pthread_t cyclists[number_of_cyclists];
    for(int i = 0; i < number_of_cyclists; i++){
        int* id = new int;
        *id = i + 1;

        res = pthread_create(&cyclists[i],NULL,get_service,(void *)id);

        if(res != 0){
            printf("Thread creation failed\n");
        }
    }


    // joining threads
    for(int i = 0; i < number_of_cyclists; i++){
        void *result;
        pthread_join(cyclists[i],&result);
        //printf("%s hatir matha\n",(char*)result);
    }


    // destroying mutex, condVar & sem_t
    res = sem_destroy(&empty_payment_room);
    if(res != 0){
        printf("Failed\n");
    }

    res = pthread_cond_destroy(&cond);
    if(res != 0){
        printf("Failed\n");
    }

    for (int i = 0; i < number_of_servicemen; i++) {
        res = pthread_mutex_destroy(&mutex[i]);
        if(res != 0){
            printf("Failed\n");
        }
    }

    return 0;
}
