/**
 * File              : p2.c
 * Author            : Souleymane Dembele <sdembele@uw.edu>
 * Date              : 11.04.2023
 * Last Modified Date: 11.05.2023
 * Last Modified By  : Souleymane Dembele <sdembele@uw.edu>
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int n = 2000;
// a is a nxn matrix
// b is a nxn matrix
// c is a nxn matrix
int **a, **b, **c;

int num_threads = 2000;

struct my_thread_arg {
  int start_row;
  int end_row;
};

void *matmul(void *arg) {
  struct my_thread_arg *my_arg = (struct my_thread_arg *)arg;

  int i, j, k;
  for (i = my_arg->start_row; i < my_arg->end_row; i++) { // row
    for (j = 0; j < n; j++) {                             // column
      for (k = 0; k < n; k++) {
        c[i][j] += a[i][k] * b[j][k]; // transpose b to get better cache
                                      // performance
      }
    }
  }
  pthread_exit(NULL);
}

void transpose(int **b, int n) {
  int i, j, temp;
  for (i = 0; i < n; i++) {       // row
    for (j = i + 1; j < n; j++) { // column
      temp = b[i][j];
      b[i][j] = b[j][i];
      b[j][i] = temp;
    }
  }
}

double get_time() {
  struct timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec + t.tv_usec * 1e-6;
}

double get_time_diff(double start, double end) { return end - start; }

double get_time_diff_ms(double start, double end) {
  return (end - start) * 1000;
}

double get_time_diff_us(double start, double end) {
  return (end - start) * 1000000;
}

void print_matrix(int **a, int n) {
  int i, j;
  for (i = 0; i < n; i++) { // row
    for (j = 0; j < n; j++) {
      printf("%d ", a[i][j]);
    }
    printf("\n");
  }
}
// matrix multiplication
int main(int argc, char *argv[]) {
  if (argc > 1) {
    num_threads = atoi(argv[1]);
    n = atoi(argv[2]);
  } else {
    printf("Usage: %s <num_threads>\n", argv[0]);
    // no command line arguments provided, ask the user
    printf("No argument provided, please provide the number of threads\n");
    // request number of threads from the user
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);
    printf("Enter the size of the matrix: ");
    scanf("%d", &n);
  }

  // display the number of threads and the size of the matrix
  printf("Number of threads: %d\n", num_threads);
  printf("Size of the matrix: %d\n", n);

  // display wait message
  printf("Please wait while the program is running...\n");

  pthread_t threads[num_threads];
  struct my_thread_arg args[num_threads];
  int i, j;

  // allocate memory for a 3x3 matrix
  a = (int **)malloc(
      sizeof(int *) * n *
      n); // a is a pointer to a pointer to an int (2D array) of size n*n (3x3)
  b = (int **)malloc(sizeof(int *) * n);
  c = (int **)malloc(sizeof(int *) * n);

  for (i = 0; i < n; i++) {
    a[i] = (int *)malloc(sizeof(int) * n);
    b[i] = (int *)malloc(sizeof(int) * n);
    c[i] = (int *)malloc(sizeof(int) * n);
  }

  // initialize the matrices with random values
  srand(time(NULL)); // seed the random number generator with the current
  // time (so that we get different values each time we run the program)
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      a[i][j] = rand() % 10; // rand() returns a random number between 0 and
                             // RAND_MAX (defined in stdlib.h)
      b[i][j] = rand() % 10;
      c[i][j] = 0;
    }
  }
  /**
    printf("Before:\n");
    printf("Matrix A:\n");
    print_matrix(a, n);
    printf("Matrix B:\n");
    print_matrix(b, n);
    printf("Matrix C:\n");
    print_matrix(c, n);
  **/
  // start the timer to measure the execution time of the matrix multiplication
  double start, end, time_diff, time_diff_ms, time_diff_us;
  start = get_time();
  transpose(b, n);
  for (i = 0; i < num_threads; i++) {
    args[i].start_row = i * n / num_threads;
    args[i].end_row = (i + 1) * n / num_threads;
    pthread_create(&threads[i], NULL, matmul, (void *)&args[i]);
  }

  // wait for the threads to finish
  for (i = 0; i < num_threads; i++) {
    pthread_join(threads[i], NULL);
  }

  end = get_time();

  time_diff = get_time_diff(start, end);
  time_diff_ms = get_time_diff_ms(start, end);
  time_diff_us = get_time_diff_us(start, end);

  // display the execution time

  printf("\nTime with transpose:\n");
  printf("Time taken: %f seconds\n", time_diff);
  printf("Time taken: %f milliseconds\n", time_diff_ms);
  printf("Time taken: %f microseconds\n", time_diff_us);
  /**   printf("After:\n");
     printf("Matrix A:\n");
     print_matrix(a, n);
     printf("Matrix B:\n");
     print_matrix(b, n);
     printf("Matrix C:\n");
     print_matrix(c, n);
   **/
  for (i = 0; i < n; i++) {
    free(a[i]); // free the memory allocated for each row of a
    free(b[i]);
    free(c[i]);
  }

  free(a); // free the memory allocated for the pointers to the rows of a (the
           // 2D array)
  free(b);
  free(c);

  return 0;
}
