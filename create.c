/* 
 * This file contains the Read_Data function that creates the Two-Dimensional Array.
 * The function should allocate memory, read the data, and return a two-dimensional
 * array that contains the data.
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * This function reads data from stdin and stores it in a two-dimensional array.
 * Params: int rows, int cols
 * Returns: float **data
 */
float **read_data(int rows, int cols) {

    // Allocate memory for the two-dimensional array
    float **data = (float **)malloc(rows * sizeof(float *));
    for (int i = 0; i < rows; i++) {
        data[i] = (float *)malloc(cols * sizeof(float));
    }

    // Read the data, storing as a floats in the two-dimensional array
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            //Need to read via stdin
            scanf("%f", &data[i][j]);
        }
    }

    return data;
}
