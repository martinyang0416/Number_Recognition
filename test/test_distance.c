#include <stdio.h>
#include <stdlib.h>
#include "knn.h"

/* This small test file will help you determine if you have successfully
 * completed the distance function in knn.
 * 
 * compile this program as "gcc -Wall -g -std=gnu99 -lm -o test_distance test_distance.c knn.c"
 * This program prints the image to standard output, so you should redirect it
 * to a file and compare it with the original image.
 */
unsigned char image_a[NUM_PIXELS];
unsigned char image_b[NUM_PIXELS];


int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s imagefile\n", argv[0]);
        exit(1);
    }
    
    load_image(argv[1], image_a);
    load_image(argv[2], image_b);
    double dist = distance(image_a, image_b);
    printf("%lf\n", dist);
    return 0;
}
