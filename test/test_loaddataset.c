#include <stdio.h>
#include <stdlib.h>
#include "knn.h"

/* This small test file will help you determine if you have successfully
 * completed the load_dataset function in knn.
 * 
 * compile this program as "gcc -Wall -g -std=gnu99 -lm -o test_loaddataset test_loaddataset.c knn.c"
 * This program prints the image to standard output, so you should redirect it
 * to a file and compare it with the original image.
 */
unsigned char dataset[MAX_SIZE][NUM_PIXELS];
unsigned char labels[MAX_SIZE];

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s imagefile\n", argv[0]);
        exit(1);
    }
    
    int total = load_dataset(argv[1], dataset, labels);
    printf("%d\n", total);
    for (int i = 0; i < NUM_PIXELS; i++) {
    	printf("%d ", dataset[1][i]);
    	if ((i + 1) % WIDTH == 0) {
            printf("\n");
        }
    }
    
    return 0;
}
