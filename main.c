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

int main(int argc, char *argv[]) {
    // checking for the correct amount of arguments in input
    int numReaders;

    printf("Enter number of readers: \n");
    scanf("%d", &numReaders);

    /*
    if (argc != 2) {
        printf("Usage: %s <number_of_readers>\n", argv[0]);
        return 1;
    }
    */

    // checking if number of readers is in the correct range
    //int numReaders = atoi(argv[1]);
    if (numReaders < 0 || numReaders > MAX_READERS) {
        printf("Number of readers must be between 1 and 12.\n");
        return 1;
    }

    printf("Executing... please wait...\n");

    for (int count = 0; count < 25000; count++) {
        sharedCounter++;
    }

    printf("Writer Done!\n");

    for (int reader = 0; reader < numReaders; reader++) {
        printf("I'm reader%d, counter = %d\n", reader + 1, sharedCounter);
    }
}
