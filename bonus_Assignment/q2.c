#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N
#define FREE 0
#define USE 1
int state[N];
int state_fork[N];
int phil[N] = { 0, 1, 2, 3, 4 };
sem_t bowl;
sem_t mutex;
sem_t mutex2;
sem_t S[N];

int test(int phnum)
{
	if (state[phnum] == HUNGRY){
        if(state_fork[phnum] == FREE && state_fork[LEFT] == FREE){
            sem_wait(&bowl);
            int a;
            sem_getvalue(&bowl, &a);
            printf("Philosopher %d takes a bowl (left: %d) \n", phnum + 1, a);
            int t = rand() % 2;
            int x;
            if(t == 0){
                x = phnum;
            }
            else{
                x = LEFT;
            }
            state[x] = EATING;
            state_fork[x] = USE;
            sleep(2);
            printf("Philosopher %d takes fork %d\n",phnum + 1, x + 1);
            printf("Philosopher %d is Eating\n", phnum + 1);

            // sem_post(&S[phnum]) has no effect
            // during takefork
            // used to wake up hungry philosophers
            // during putfork
            sem_post(&S[phnum]);
            return x;
        }
        else if(state_fork[phnum] == FREE){
            // state that eating
            sem_wait(&bowl);
            state[phnum] = EATING;
            state_fork[phnum] = USE;
            sleep(2);
            printf("Philosopher %d takes fork %d\n",phnum + 1,  phnum + 1);
            printf("Philosopher %d is Eating\n", phnum + 1);

            // sem_post(&S[phnum]) has no effect
            // during takefork
            // used to wake up hungry philosophers
            // during putfork
            sem_post(&S[phnum]);
            return phnum;
        } 
        else if (state_fork[LEFT] == FREE) {
            // state that eating
            sem_wait(&bowl);
            state[phnum] = EATING;
            state_fork[phnum] = USE;
            sleep(2);
            printf("Philosopher %d takes fork %d \n",phnum + 1, LEFT + 1);
            printf("Philosopher %d is Eating\n", phnum + 1);

            // sem_post(&S[phnum]) has no effect
            // during takefork
            // used to wake up hungry philosophers
            // during putfork
            sem_post(&S[phnum]);
            return LEFT;
	    }
    }

}

// take up chopsticks
int take_fork(int phnum)
{

	sem_wait(&mutex);

	// state that hungry
	state[phnum] = HUNGRY;

	printf("Philosopher %d is Hungry\n", phnum + 1);
    sleep(1);
	// eat if neighbours are not eating
	int res = test(phnum);
	sem_post(&mutex);

	// if unable to eat wait to be signalled
	sem_wait(&S[phnum]);
    //printf("xaiefjuoiahfd\n");
	sleep(1);
    return res;

}

// put down chopsticks
void put_fork(int phnum, int x)
{
    //printf("lfeijskdshfskj\n");
	sem_wait(&mutex2);
    
	// state that thinking
    sem_post(&bowl);
	state[phnum] = THINKING;
    state_fork[x] = FREE;
	// printf("Philosopher %d putting fork %d and %d down\n",phnum + 1, LEFT + 1, phnum + 1);
	printf("Philosopher %d is thinking\n", phnum + 1);

	test(LEFT);
	test(RIGHT);
	sem_post(&mutex2);
}

void* philosopher(void* num)
{

	while (1) {

		int* i = num;

		sleep(1);

		int result = take_fork(*i);

		sleep(0);

		put_fork(*i, result);
        printf("\n\n");
	}
}

int main()
{

	int i;
	pthread_t thread_id[N];

	// initialize the semaphores
	sem_init(&mutex, 0, 1);
    sem_init(&mutex2, 0, 1);
    sem_init(&bowl, 0, 4);
	for (i = 0; i < N; i++){
        state_fork[i] = FREE;    
		sem_init(&S[i], 0, 0);
    }
	for (i = 0; i < N; i++) {

		// create philosopher processes
		pthread_create(&thread_id[i], NULL,
					philosopher, &phil[i]);

		printf("Philosopher %d is thinking\n", i + 1);
	}

	for (i = 0; i < N; i++)

		pthread_join(thread_id[i], NULL);
}
