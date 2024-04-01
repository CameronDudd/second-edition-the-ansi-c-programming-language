// Copyright 2024 Cameron Dudd
// Examples from "SECOND EDITION THE C (ANSI C) PROGRAMMING LANGUAGE - BRIAN
// W.KERNIGHAN DENNIS M.RITCHIE"

#include <stdio.h>

#define IN 1
#define OUT 2

/* count lines, words, and characters in input */
int main() {
  int c, nl, nw, nc, state;

  state = OUT;
  nl = nw = nc = 0;

  while ((c = getchar()) != EOF) {
    ++nc;
    if (c == '\n')
      ++nl;
    if (c == ' ' || c == '\n' || c == '\t') {
      state = OUT;
    } else if (state == OUT) {
      state = IN;
      ++nw;
    }
    printf("%d %d %d\n", nl, nw, nc);
  }

  return 1;
}
