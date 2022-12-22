#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
sem_t chopstick[5];
#define PHILOSPHERS 5
void * philos(void *);
void eat(int);
int main()
 {
         int n[PHILOSPHERS];
         pthread_t T[PHILOSPHERS];
         int i =0;
         while(i<PHILOSPHERS){
                sem_init(&chopstick[i],0,1);
                i++;
            }
        i = 0;
         while(i<PHILOSPHERS){
                n[i]=i;
                pthread_create(&T[i],NULL,philos,(void *)&n[i]);
                i++;
            }
            i = 0;
        while(i<PHILOSPHERS){
                 pthread_join(T[i],NULL);
                 i ++;
         }
         i = 0;
 }
void * philos(void * n)
 {
         int ph=*(int *)n;
         if(ph!=3){
            printf("Philosopher %d wants to eat\n",ph);
            printf("Philosopher %d tries to pick left chopstick\n",ph);
            sem_wait(&chopstick[ph]);
            printf("Philosopher %d picks the left chopstick\n",ph);
            printf("Philosopher %d tries to pick the right chopstick\n",ph);
            sem_wait(&chopstick[(ph+1)%PHILOSPHERS]);
            printf("Philosopher %d picks the right chopstick\n",ph);
            printf("Philosopher %d begins to eat\n",ph);
            sleep(2);
            printf("Philosopher %d has finished eating\n",ph);
            sem_post(&chopstick[(ph+1)%PHILOSPHERS]);
            printf("Philosopher %d leaves the right chopstick\n",ph);
            sem_post(&chopstick[ph]);
            printf("Philosopher %d leaves the left chopstick\n",ph);
         }else if(ph==3){
            printf("Philosopher %d wants to eat\n",ph);
            printf("Philosopher %d tries to pick left chopstick\n",ph);
            sem_wait(&chopstick[(ph+1)%PHILOSPHERS]);
            printf("Philosopher %d picks the left chopstick\n",ph);
            printf("Philosopher %d tries to pick the right chopstick\n",ph);
            sem_wait(&chopstick[ph]);
            printf("Philosopher %d picks the right chopstick\n",ph);
            printf("Philosopher %d begins to eat\n",ph);
            sleep(2);
            printf("Philosopher %d has finished eating\n",ph);
            sem_post(&chopstick[ph]);
            printf("Philosopher %d leaves the right chopstick\n",ph);
            sem_post(&chopstick[(ph+1)%PHILOSPHERS]);
            printf("Philosopher %d leaves the left chopstick\n",ph);
         }
 }