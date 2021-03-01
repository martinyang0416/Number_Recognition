#include <stdio.h>
#include <math.h>    // Need this for sqrt()
#include <stdlib.h>
#include <string.h>

#include "knn.h"


/* Print the image to standard output in the pgmformat.  
 * (Use diff -w to compare the printed output to the original image)
 */
void print_image(unsigned char *image) {
    printf("P2\n %d %d\n 255\n", WIDTH, HEIGHT);
    for (int i = 0; i < NUM_PIXELS; i++) {
        printf("%d ", image[i]);
        if ((i + 1) % WIDTH == 0) {
            printf("\n");
        }
    }
}

/* Return the label from an image filename.
 * The image filenames all have the same format:
 *    <image number>-<label>.pgm
 * The label in the file name is the digit that the image represents
 */
unsigned char get_label(char *filename) {
    // Find the dash in the filename
    char *dash_char = strstr(filename, "-");
    // Convert the number after the dash into a integer
    return (char) atoi(dash_char + 1);
}

/* ******************************************************************
 * Complete the remaining functions below
 * ******************************************************************/


/* Read a pgm image from filename, storing its pixels
 * in the array img.
 * It is recommended to use fscanf to read the values from the file. First, 
 * consume the header information.  You should declare two temporary variables
 * to hold the width and height fields. This allows you to use the format string
 * "P2 %d %d 255 "
 * 
 * To read in each pixel value, use the format string "%hhu " which will store
 * the number it reads in an an unsigned character.
 * (Note that the img array is a 1D array of length WIDTH*HEIGHT.)
 */
void load_image(char *filename, unsigned char *img) {
    // Open corresponding image file, read in header (which we will discard)
    FILE *f2 = fopen(filename, "r");
    if (f2 == NULL) {
        perror("fopen");
        exit(1);
    }

    int column;
    int row;

    fscanf(f2, "P2 %d %d 255 ", &column, &row);

    for(int i = 0; i < 784; i ++){
        fscanf(f2, "%hhu ", img + i);
    }

    fclose(f2);
}


/**
 * Load a full dataset into a 2D array called dataset.
 *
 * The image files to load are given in filename where
 * each image file name is on a separate line.
 * 
 * For each image i:
 *  - read the pixels into row i (using load_image)
 *  - set the image label in labels[i] (using get_label)
 * 
 * Return number of images read.
 */
int load_dataset(char *filename, 
                 unsigned char dataset[MAX_SIZE][NUM_PIXELS],
                 unsigned char *labels) {
    // We expect the file to hold up to MAX_SIZE number of file names
    FILE *f1 = fopen(filename, "r");
    if (f1 == NULL) {
        perror("fopen");
        exit(1);
    }

    char names_of_file[MAX_SIZE];
    int current = 0;
    // int max_length = 300; 

    while(fscanf(f1, "%s", names_of_file) != EOF){
        load_image(names_of_file, dataset[current]);
        labels[current] = get_label(names_of_file);
        current += 1;
    }

    fclose(f1);
    return current;
}


/** 
 * Return the euclidean distance between the image pixels in the image
 * a and b.  (See handout for the euclidean distance function)
 */
double distance(unsigned char *a, unsigned char *b) {
    double total = 0.0;

    for(int index = 0; index < NUM_PIXELS; index++){

        int frist = a[index];
        int second = b[index];
        total += pow(frist - second, 2.0);
    }

    total = sqrt(total);
    return total;
}


/**
 * Return the most frequent label of the K most similar images to "input"
 * in the dataset
 * Parameters:
 *  - input - an array of NUM_PIXELS unsigned chars containing the image to test
 *  - K - an int that determines how many training images are in the 
 *        K-most-similar set
 *  - dataset - a 2D array containing the set of training images.
 *  - labels - the array of labels that correspond to the training dataset
 *  - training_size - the number of images that are actually stored in dataset
 * 
 * Steps
 *   (1) Find the K images in dataset that have the smallest distance to input
 *         When evaluating an image to decide whether it belongs in the set of 
 *         K closest images, it will only replace an image in the set if its
 *         distance to the test image is strictly less than all of the images in 
 *         the current K closest images.
 *   (2) Count the frequencies of the labels in the K images
 *   (3) Return the most frequent label of these K images
 *         In the case of a tie, return the smallest value digit.
//  */ 

int knn_predict(unsigned char *input, int K,
                unsigned char dataset[MAX_SIZE][NUM_PIXELS],
                unsigned char *labels,
                int training_size){
    
    int top_labels[K];
    int top_index[K];
    double top_values[K];

    double largest_value = -10000.0;
    int largest_index = 0;
    
    for(int index = 0; index < training_size; index++){

        double current_value = distance(dataset[index], input);
        int current_label = (int)labels[index];

        if(index < K){
            top_labels[index] = current_label;
            top_index[index] = index;
            top_values[index] = current_value;
            // one place need to consider < or <= ! check later 
            if(current_value > largest_value){
                largest_index = index;
                largest_value = current_value;
            }
        }else{
            if(current_value < largest_value){
                top_index[largest_index] = index;
                top_labels[largest_index] = current_label;
                top_values[largest_index] = current_value;

                // find the largest index in the array again, check < and <= in process later!
                largest_value = top_values[0];
                largest_index = 0;
                for(int index2 = 0; index2 < K; index2++){
                    if(top_values[index2] > largest_value){
                        largest_index = index2;
                        largest_value = top_values[index2];
                    }
                }
            }
        }
    }

    int highest = 1;
    int result = top_labels[0];

    for (int index3 = 0; index3 < K; index3++) {
        int cur_value = 1;
        // int index4;
        // index4 = index3 + 1;
        for (int index4 = index3 + 1; index4 < K; index4++) {
            if (top_labels[index3] == top_labels[index4]) {
                cur_value = cur_value + 1;
            }   
        }
        
        // choose the small value one if the occurency is equal.
        if (cur_value == highest) {
            if (top_labels[index3] < result) {
                result = top_labels[index3];
            }
        }else if (cur_value > highest) {
            highest = cur_value;
            result = top_labels[index3];
        }
    }
    return result;
}