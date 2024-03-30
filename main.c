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

int main(int argc, char *argv[]) {
    // checking for the correct amount of arguments in input
    if (argc != 2) {
        printf("Usage: %s <number_of_readers>\n", argv[0]);
        return 1;
    }

    // checking if number of readers is in the correct range
    int num_readers = atoi(argv[1]);
    if (num_readers <= 0 || num_readers > 12) {
        printf("Number of readers must be between 1 and 12 inclusive.\n");
        return 1;
    }
}