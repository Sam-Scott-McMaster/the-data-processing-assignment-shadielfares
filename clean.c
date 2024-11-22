/*
 * You will develop a command line utility named clean that processes a two-dimensional grid of
 * floating-point numbers for machine learning by replacing bad values with legal values.
 *
 * Some Important Info from the doc:
 *
 * Program should be able to handle a data grid of ANY SIZE.
 *
 * Also:
 *
 * If the -d flag is used, the app cleans the input data using a deletion strategy (see next section).
 * Otherwise, it cleans it using the imputation strategy also described in the next section
 */

//This file is the main file and must contain the .h imports.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "manipulate.h"
#include "create.h"

/*
 * This function prints the usage of the program
 * Params: None
 * Returns: void
 */
void print_usage(){
    fprintf(stderr,"Usage: clean [-d] <datafile.txt >cleanedfile.txt\nOR\nclean <datafile.txt >cleanedfile.txt\n");
}

/*
 * This is the main function that reads the data, cleans it, and outputs the cleaned data.
 * Params: int argc, char *argv[]
 * Returns: int
 */
int main(int argc, char *argv[]) {
    //Start loop at 1, to avoid the first argument which is the name of the program
    int flag, rows, cols;

    for (int i = 1; i < argc; i++) {
        //Check # of arguments
        if (argc < 1) {
            print_usage();
        }
        //Check if the -d flag is used
        if (strcmp(argv[i], "-d") == 0 && argc == 2) {
            //If the -d flag is used, the app cleans the input data using a deletion strategy
            //I will use a flag to check if the -d flag is used
            flag = 1;
        } else {
            //Otherwise, it cleans it using the imputation strategy
            flag = 0;
        }
    }

    //Need to read the first line of the file to get the number of rows and columns
    scanf("%d %d", &rows, &cols);

    float **data = read_data(rows, cols);
    if (flag == 1) {
        //Segmentation happening here
        float **result = clean_delete(data, &rows, cols);
        //Now I need to output the data but with the new valid row amount, the columns are fine as is
        output_data(result, rows, cols);
    } else {
        clean_impute(data, rows, cols);
        output_data(data, rows, cols);
    }
    free(data);
}
