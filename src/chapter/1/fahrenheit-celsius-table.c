// Copyright 2024 Cameron Dudd
// Examples from "SECOND EDITION THE C (ANSI C) PROGRAMMING LANGUAGE - BRIAN
// W.KERNIGHAN DENNIS M.RITCHIE"

#include <stdio.h>

#define LOWER 0   /* lower limit of temperature table */
#define UPPER 300 /* upper limit */
#define STEP 20   /* step size */

/* print Fahrenheit-Celsius table
 * for fahr = 0, 20, ..., 300 */
int main() {
  float fahr, celsius;

  fahr = LOWER;
  printf("+------------+---------+\n");
  printf("| Fahrenheit | Celsius |\n");
  printf("+------------+---------+\n");
  while (fahr <= UPPER) {
    celsius = 5 * (fahr - 32) / 9;
    printf("| %10.0f | %7.2f |\n", fahr, celsius);
    fahr = fahr + STEP;
  }
  printf("+------------+---------+\n");
}
