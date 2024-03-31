// Cairo Crawford PantherID: 6389250
// Cedric Cherestal PantherID: 5512167
// Camila Castaneda PantherID: 6059028
//
// This program is a solution to the n readers 1 writer problem. It will take
// input from the command line stating the amount of readers then the readers
// will access the shared counter variable 2000000 total times. In this same
// time, the writer will increment the counter 25000 times. When done, each of
// the readers will print their name as well as the value of the shared counter

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_READERS 12
#define NUM_READS 2000000
#define NUM_WRITES 25000

volatile int sharedCounter = 0;
sem_t mutex, wrt;
int readCount = 0;

void *reader(void *param);
void *writer(void *param);

int main(int argc, char *argv[])
{

   //performing input validation
   if (argc != 2)
   {
        printf("Usage: %s <number of readers>\n", argv[0]);
        return 1;
    }

    int numReaders = atoi(argv[1]);
    if (numReaders < 1 || numReaders > MAX_READERS)
    {
        printf("Number of readers must be between 1 and 12.\n");
        return 1;
    }


    // Initializing sempahores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    pthread_t readers[numReaders], writer_thread;
    int readerNums[numReaders];

    printf("Executing... please wait...\n");

    // Create the writer thread
    pthread_create(&writer_thread, NULL, writer, NULL);

    // Create reader threads
    for (int i = 0; i < numReaders; i++)
    {
        readerNums[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &readerNums[i]);
    }

    // Wait for the writer to finish
    pthread_join(writer_thread, NULL);

    // Wait for all readers to finish
    for (int i = 0; i < numReaders; i++)
    {
        pthread_join(readers[i], NULL);
    }

    return 0;
}

// The reader function that will be executed by each reader thread.
void *reader(void *param)
{
    // pull reader number from parameter
    int readerNum = *((int *)param);

    for (int i = 0; i < NUM_READS; i++)
    {
        // Wait to acquire the mutex before modifying readCount.
        // if there's an error, exit the program
        if (sem_wait(&mutex) != 0)
        {
            perror("sem_wait (mutex) in reader failed");
            exit(1);
        }

        readCount++;

        // Checks if this is the first reader. If so, it must wait. prints error
        // code if it fails
        if (readCount == 1)
        {
            if (sem_wait(&wrt) != 0)
            {
                perror("sem_wait (wrt) in reader failed");
                exit(1);
            }
        }

        // Release the mutex to allow other readers to increment the readCount
        if (sem_post(&mutex) != 0)
        {
            perror("sem_post (mutex) in reader failed");
            exit(1);
        }

        // Critical section (reading)

        if (sem_wait(&mutex) != 0)
        {
            perror("sem_wait (mutex) in reader failed");
            exit(1);
        }

        // to show this reader has finished reading
        readCount--;

        // checks if its the last reader, if so, it must release semaphore
        if (readCount == 0)
        {
            if (sem_post(&wrt) != 0)
            {
                perror("sem_post (wrt) in reader failed");
                exit(1);
            }
        }
        if (sem_post(&mutex) != 0)
        {
            perror("sem_post (mutex) in reader failed");
            exit(1);
        }
    }

    printf("I'm reader%d, counter = %d\n", readerNum, sharedCounter);
    return;
}

//writer function executed by the writer thread
void *writer(void *param) {
    for (int i = 0; i < NUM_WRITES; i++)
    {
        // Wait to acquire the write semaphore (wrt) before proceeding
        // print an error and exit if theres a failure
        if (sem_wait(&wrt) != 0)
        {
            perror("sem_wait (wrt) in writer failed");
            exit(1);
        }

        // Critical section starts
        sharedCounter++;

        // print an error and exit if theres a failure
        if (sem_post(&wrt) != 0)
        {
            perror("sem_post (wrt) in writer failed");
            exit(1);
        }
    }

    printf("Writer Done!\n");
    return;
}
