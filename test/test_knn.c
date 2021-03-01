#include <stdio.h>
#include <stdlib.h>
#include "knn.h"

/* This small test file will help you determine if you have successfully
 * completed the knn_predict function in knn.
 * 
 * compile this program as "gcc -Wall -g -std=gnu99 -lm -o test_knn_predict test_knn_predict.c knn.c"
 * This program prints the image to standard output, so you should redirect it
 * to a file and compare it with the original image.
 */
unsigned char training_dataset[MAX_SIZE][NUM_PIXELS];
unsigned char training_labels[MAX_SIZE];
unsigned char testing_image[NUM_PIXELS];


int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s imagefile\n", argv[0]);
        exit(1);
    }
    char *training_file_list = argv[2];
	char *test_file = argv[3];
	int K = strtod(argv[1], NULL);
	int num_training_files = load_dataset(training_file_list, training_dataset, training_labels);
	load_image(test_file, testing_image);
    
    int predict_label = knn_predict(testing_image, K, training_dataset, training_labels, num_training_files);
    printf("predict label: %d.\n", predict_label);
    return 0;
}
