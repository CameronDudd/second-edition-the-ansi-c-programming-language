// Copyright 2024 Cameron Dudd
// Examples from "SECOND EDITION THE C (ANSI C) PROGRAMMING LANGUAGE - BRIAN
// W.KERNIGHAN DENNIS M.RITCHIE"

#include <stdio.h>

/* copy input to output; 1st version */
int main() {
  int c;

  c = getchar();
  while (c != EOF) {
    putchar(c);
    c = getchar();
  }
  return 1;
}
