#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <math.h>

void draw_matrix();
int menu();
void maximax();
void maximin();
void hurwicz();
void laplace();
void savage_niehans();
void bayes();
void u_sigma();
void bernoulli();

const int rows = 5;
const int columns= 3;

const int e_matrix[rows][columns] = {
    {0, 18000, 20000 },
    {6500, 8500, 10000},
    {5000, 10000, 15000},
    {7000, 8000, 11000},
    {6500, 6500, 6500},
};

const float p_matrix[rows][columns] = {
    {0.1, 0.8, 0.1},
    {0.2, 0.3, 0.5},
    {0.3, 0.4, 0.3},
    {0.2, 0.1, 0.7},
    {0.4, 0.4, 0.2},
};

int main() {
    int selection;

    draw_matrix();

    for(;;) {
        selection = menu();

        switch(selection) {
            case 1:
                maximax();
                break;
            case 2:
                maximin();
                break;
            case 3:
                hurwicz();
                break;
            case 4:
                laplace();
                break;
            case 5:
                savage_niehans();
                break;
            case 6:
                bayes();
                break;
            case 7:
                u_sigma();
                break;
            case 8:
                bernoulli();
                break;
        }
        if(selection == 0) break;
    }
    return 0;
}

void draw_matrix() {
    int i;

    printf("\n\n## MATRIX\n\n");
    for(i=0; i<5; i++) {
        printf("| %i %i %i |\n\n", e_matrix[i][0], e_matrix[i][1], e_matrix[i][2] );
    }
}

int menu() {
    int input;

    printf("## MENU\n\n");
    printf("1. Maximax Rule\n");
    printf("2. Maximin Rule\n");
    printf("3. Hurwicz Rule\n");
    printf("4. Laplace Rule\n");
    printf("5. Savage-Niehans Rule\n");
    printf("6. Bayes Principle (u-Rule)\n");
    printf("7. u-Sigma Rule\n");
    printf("8. Bernoulli Principle\n");
    printf("0. ENDE\n\n");
    printf("Please selection select the Method: ");

    scanf("%i", &input);

    return input;
}

void maximax() {
    int i, j, result_row = 0, result_value = 0, max_row[rows];

    printf("\n## MAXIMAX\n\n");

    for(i=0; i < rows; i++) max_row[i] = 0;

    for(i=0; i < rows; i++) {
        for(j=0; j < columns; j++) {
            if ( max_row[i] < e_matrix[i][j] ) max_row[i] = e_matrix[i][j]; // get maximum of rows
        }
    }

    // Show results
    printf("RESULT\n\n");
    for(i=0; i < rows; i++) printf("Row #%i: L = %i (max)\n", i+1, max_row[i]);

    for(i=0; i < rows; i++) {
        if(result_value < max_row[i]) {
            result_value = max_row[i];
            result_row = i;
        }
    }
    printf("\n-> Result: %i in row %i (max)\n\n", result_value, result_row+1); // the result
}

void maximin() {
    int i, j, result_row = 0, result_value = 0, min_row[rows];

    printf("\n## MAXIMIN\n\n");

    for(i=0; i < rows; i++) min_row[i] = 30000;

    for(i=0; i < rows; i++) {
        for(j=0; j < columns; j++) {
            if ( min_row[i] > e_matrix[i][j] ) min_row[i] = e_matrix[i][j]; // get minimum of the rows
        }
    }

    // Show results
    printf("RESULT\n\n");
    for(i=0; i < rows; i++) printf("Row #%i: L = %i (min)\n", i+1, min_row[i]);

    for(i=0; i < rows; i++) {
        if(result_value < min_row[i]) {
            result_value = min_row[i];
            result_row = i;
        }
    }

    printf("\n-> Result: %i in row %i (max)\n\n", result_value, result_row+1); // the result
}

void hurwicz() {
    int i, j, result_row = 0;
    float lambda = 0, result_value[rows], max_row[rows], min_row[rows], result_final = 0;

    printf("\n\n## HURWICZ\n\nBitte Lambda eingeben (0 = risikoscheu, 1 = risikofreudig): ");

    scanf("%f", &lambda);

    for(i=0; i < rows; i++) {
        max_row[i] = 0; // Array mit 0 initialisieren
        min_row[i] = 30000; // Array mit 30000 initialisieren
    }

    for(i=0; i < rows; i++) {
        for(j=0; j < columns; j++) { // MAX
            if ( max_row[i] < e_matrix[i][j] ) max_row[i] = e_matrix[i][j]; // get maximum of the rows
            if ( min_row[i] > e_matrix[i][j] ) min_row[i] = e_matrix[i][j]; // get minimum of the rows
        }
        result_value[i] = (max_row[i] * lambda) + (min_row[i] * (1-lambda));
    }

    // Show results
    printf("\n\nRESULT\n\n");
    for(i=0; i < rows; i++) printf("Row #%i: L = %f\n", i+1, result_value[i]), min_row[i], max_row[i];

    for(i=0; i < rows; i++) { // MAX
        if(result_final < result_value[i]) {
            result_final = result_value[i];
            result_row = i;
        }
    }
    printf("\n-> Result: %f in row %i (max)\n\n", result_final, result_row+1); // the result
}

void laplace() {
    int i, j, row_of_result = 0;
    float result_row[rows], result = 0;

    printf("\n\n## LAPLACE\n");

    for(i=0; i < rows; i++) {
        result_row[i] = 0;
    }

    for(i=0; i < rows; i++) {
        for(j=0; j < columns; j++) {
            result_row[i] = e_matrix[i][j] + result_row[i]; // sum up all row elements
        }
        result_row[i] = result_row[i]/columns; // divide it by number of columns
    }

    // Show results
    printf("\nRESULT\n\n");
    for(i=0; i < rows; i++) printf("Row #%i: L = %f (sum)\n", i+1, result_row[i]);

    for(i=0; i < rows; i++) { // MAX
        if(result < result_row[i]) {
            result = result_row[i];
            row_of_result = i;
        }
    }
    printf("\n-> Result: %f in row %i (max)\n\n", result, row_of_result+1); // the result
}

void savage_niehans() {
    int i, j, k;
    int result_row[rows], max_col[columns], max_row[rows], result_final = 30000, row_of_result = 0;

    printf("\n\n## SAVAGE-NIEHANS\n\n");

    for(i=0; i < rows; i++) {
        max_row[i] = 0; // Array mit 0 initialisieren
    }

    for(i=0; i < columns; i++) {
        max_col[i] = 0; // Array mit 0 initialisieren
    }

    for(i=0; i < rows; i++) {
        for(j=0; j < columns; j++) {
            for(k=0; k < rows; k++) {
                if(max_col[j] < e_matrix[k][j]) max_col[j] = e_matrix[k][j]; // get maximum of the columns
            }
            max_col[j] = max_col[j] - e_matrix[i][j];
            if (max_row[i] < max_col[j]) max_row[i] = max_col[j]; // get maximum of the rows
        }
    }

    // Show results
    printf("RESULT\n\n");
    for(i=0; i < rows; i++) printf("Row #%i: L = %i (max)\n", i+1, max_row[i]);

    for(i=0; i < rows; i++) { // MIN
        if(result_final > max_row[i]) {
            result_final = max_row[i];
            row_of_result = i;
        }
    }
    printf("\n-> Result: %i in row %i (min)\n\n", result_final, row_of_result+1); // the result
}

void bayes() {
    float result_rows[rows], result_value = 0;
    int i,  j, result_row;

    printf("\n\n## BAYES (u-Rule)\n\n");

    for(i=0; i < rows; i++) result_rows[i] = 0;

    for(i=0; i < rows; i++) {
        for(j=0; j < columns; j++) {
            result_rows[i] = result_rows[i] + ( e_matrix[i][j] * p_matrix[i][j] ); // factorize event with possibility of event and sum this row-wise up
        }
    }

    // Show results
    printf("\RESULT\n\n");
    for(i=0; i < rows; i++) printf("Row #%i: L = %f (sum)\n", i+1, result_rows[i]);

    for(i=0; i < rows; i++) {
        if(result_value < result_rows[i]) {
            result_value = result_rows[i];
            result_row = i;
        }
    }
    printf("\n-> Result: %f in row %i (max)\n\n", result_value, result_row+1); // the result
}

void bernoulli() {
    double result_rows[rows], result_value = 0;
    int i,  j, result_row, x;

    printf("\n\n## BERNOULLI\nFunction: U(x) = ln(x)/10\n\n");

    for(i=0; i < rows; i++) result_rows[i] = 0;

    for(i=0; i < rows; i++) {
        for(j=0; j < columns; j++) {
            result_rows[i] = result_rows[i] + ( ( (log(e_matrix[i][j] + 10) / log(2.718281828) ) ) ) / 10 * p_matrix[i][j]; // ln of (event * possibility of event) and sum this row-wise up; shift of the function by 10
        }
    }

    // Show results
    printf("\RESULT\n\n");
    for(i=0; i < rows; i++) printf("Row #%i: L = %f (sum)\n", i+1, result_rows[i]);

    for(i=0; i < rows; i++) {
        if(result_value < result_rows[i]) {
            result_value = result_rows[i];
            result_row = i;
        }
    }
    printf("\n-> Result: %f in row %i (max)\n\n", result_value, result_row+1); // the result
}

void u_sigma() {
    float result_rows_out[rows], result_rows_mid[rows], result_rows_in[rows], result_value = 0, lambda, result_final[rows], q;
    int i,  j, k, result_row;

    printf("\n\n## u-Sigma Rule)\n\n");

    printf("Bitte Lambda eingeben: ");

    scanf("%f", &lambda);

    for(i=0; i < rows; i++) {
        result_rows_mid[i] = 0;
        result_rows_out[i] = 0;
        result_rows_in[i] = 0;
    }

    for(i=0; i < rows; i++) {
        for(j=0; j < columns; j++) {
            for(k=0; k < columns; k++) {
                result_rows_in[i] = result_rows_in[i] + (e_matrix[i][k] * p_matrix[i][k]);
            }
            result_rows_mid[i] = result_rows_mid[i] + ( ( ( (e_matrix[i][j] - result_rows_in[i]) * (e_matrix[i][j] - result_rows_in[i]) ) ) *  p_matrix[i][j] );
            result_rows_out[i] = result_rows_out[i] + ( e_matrix[i][j] * p_matrix[i][j] );
        }
        result_final[i] = result_rows_out[i] + q * sqrt(result_rows_mid[i]);
    }


    // Show results
    printf("\RESULT\n\n");
    for(i=0; i < rows; i++) printf("Row #%i: L = %f (sum)\n", i+1, result_final[i]);

    for(i=0; i < rows; i++) {
        if(result_value < result_final[i]) {
            result_value = result_final[i];
            result_row = i;
        }
    }
    printf("\n-> Result: %f in row %i (max)\n\n", result_value, result_row+1); // the result
}


/* IMPROVEMENTS
* Bessere Menüführung
* Dynamisches Erzeugen des Arrays durch eingabe => Übergabe des Arrays via Pointer
*
*
*/
