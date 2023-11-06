/**
 * File              : p1.c
 * Author            : Souleymane Dembele <sdembele@uw.edu>
 * Date              : 11.03.2023
 * Last Modified Date: 11.03.2023
 * Last Modified By  : Souleymane Dembele <sdembele@uw.edu>
 */
/**
Requirement 1
You must write a fully functional, single-threaded version of matrix
multiplication in C to ensure the results calculated are correctly. This
implementation should include collection of timing information immediately
before the matrix multiplication step as well as another timing call after
completing the multiplication and print the time difference. This will also give
you a baseline from which you can measure the performance impact of your
threaded version.
 * */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int main(int argc, char *argv[]) {
  int i, j, k, n;       // n is the size of the matrix
                        // a, b, c are matrices
  int **a, **b, **c;    // a, b, c are pointers to pointers to integers
  clock_t start, end;   // clock_t is a type from time.h
  double cpu_time_used; // this is a double from time.h

  if (argc != 2) { // argc is the number of arguments passed to the program
    printf("Usage: %s <n>\n", argv[0]); // argv[0] is the name of the program
    exit(1); // exit with error code 1 (general error) if argc != 2
  }

  n = atoi(argv[1]); // atoi converts a string to an integer (from stdlib.h)

  a = (int **)malloc(n *
                     sizeof(int *)); // malloc allocates memory (from stdlib.h)
  b = (int **)malloc(
      n *
      sizeof(
          int *)); // sizeof returns the size of a type in bytes (from stddef.h)

  for (i = 0; i < n;
       i++) { // initialize the matrices with random values (from stdlib.h)
              // and malloc space for each row of the matrix
    a[i] = (int *)malloc(n * sizeof(int)); // malloc returns a pointer to the
                                           // allocated memory (from stdlib.h)
    b[i] = (int *)malloc(n * sizeof(int));
  }

  c = (int **)malloc(n * sizeof(int *)); // malloc space for each row of c (the
                                         // result matrix)

  for (i = 0; i < n; i++) {
    c[i] = (int *)malloc(n * sizeof(int));
  }

  srand(time(NULL)); // srand seeds the random number generator (from stdlib.h)

  for (i = 0; i < n; i++) { // initialize the matrices with random values
    for (j = 0; j < n; j++) {
      a[i][j] = rand() % 100; // rand returns a random integer (from stdlib.h)
      b[i][j] = rand() % 100;
    }
  }

  start = clock(); // clock returns the current CPU time (from time.h)

  return 0;
}
