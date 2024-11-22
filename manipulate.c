/*
 * This file contains all the functions that are required to manipulate the data such as:
 * clean_data, clean_impute, and output_data.
 *
 * Clean_delete: This function implements a deletion strategy in which rows with bad data are deleted from an array.
 * It accepts a two-dimensional array of floats as a parameter and returns a new array that is a copy
 * of the original array in which every row that contains a nan value has been removed.
 *
 * Clean_impute: This function implements a simple imputation strategy in which each nan value in a given array is
 * be replaced with an estimate. The function accepts a two-dimensional array of floats as a
 * parameter and modifies it so that every nan value has been replaced by the average value of the
 * legal floats in that column.
 *
 * Output_data: This function implements a simple imputation strategy in which each nan value in a given array is
 * be replaced with an estimate. The function accepts a two-dimensional array of floats as a
 * parameter and modifies it so that every nan value has been replaced by the average value of the
 * legal floats in that column
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "create.h"
/*
 * This function implements a deletion strategy in which rows with bad data are deleted from an array.
 * Params: float **data, int *rows, int cols
 * Returns: float **cleaned_data
 */
float **clean_delete(float **data, int *rows, int cols) {
    // Count the number of rows with bad data
    int valid_row_count = 0; 

    // Allocate memory for cleaned_data (initially assuming max valid rows)
    float **cleaned_data = malloc(*rows * sizeof(float));
    if (cleaned_data == NULL) {
        return NULL;
    }

    //Segmentatoin happens here in the loop
    for (int i = 0; i < *rows; i++) {
        int is_bad_rows = 0;

        for (int j = 0; j < cols; j++) {
            //isNan is a function that checks if the value is a number or not...
            if (isnan(data[i][j])) {
                is_bad_rows = 1;
                break;
            }
        }

        if (!is_bad_rows) {
            cleaned_data[valid_row_count] = malloc(cols * sizeof(float));

            if (cleaned_data[valid_row_count] == NULL) {
                return NULL;
            }

            for (int j = 0; j < cols; j++) {
                cleaned_data[valid_row_count][j] = data[i][j];
            }

            valid_row_count++;
        }
    }
    *rows = valid_row_count;
    cleaned_data = realloc(cleaned_data, valid_row_count * sizeof(float *));
    return cleaned_data;
}



/*
 * This function implements a simple imputation strategy in which each nan value in a given array is
 * be replaced with an estimate. The function accepts a two-dimensional array of floats as a
 * parameter and modifies it so that every nan value has been replaced by the average value of the
 * legal floats in that column.
 * Params: float **data, int rows, int cols
 * Returns: void
 */
void clean_impute(float **data, int rows, int cols) {
    // Calculate the average value of each column
    for (int j = 0; j < cols; j++) {
        float column_sums=0;
        int column_counts=0;
        int nan_column_counts=0;

        // First pass: Calculate the sum and count of non-NaN values for this column
        for (int i = 0; i < rows; i++) {
            if (!isnan(data[i][j])) {
                column_sums += data[i][j];
                column_counts++;
            }
        }

        // Second pass: Replace NaN values with the column average
        for (int i = 0; i < rows; i++) {
            if (isnan(data[i][j])) {
                if (column_counts > 0) {
                    data[i][j] = column_sums / column_counts;
                } else {
                    data[i][j] = 0;  // Replace entire column of NaNs with 0
                }
            }
        }
    }
}

/*
 * This function outputs the data to stdout
 * Params: float **data, int rows, int cols
 * Returns: void
 */
void output_data(float **data, int rows, int cols) {
    //Need to output via stdout
    //Output the number of rows and columns
    fprintf(stdout, "%d %d\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(stdout, "%.3f ", data[i][j]);
        }
        fprintf(stdout, "\n");
    }
}
