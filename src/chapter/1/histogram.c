// Copyright 2024 Cameron Dudd
// Write a program to print a histogram of the lengths of words in its input. It
// is easy to draw the histogram with the bars horizontal; a vertical
// orientation is more challenging from "SECOND EDITION THE C (ANSI C)
// PROGRAMMING LANGUAGE - BRIAN W.KERNIGHAN DENNIS M.RITCHIE"

#include <asm-generic/ioctls.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#define IN 1
#define OUT 2
#define LARGEST_ENGLISH_WORD 45 // pneumonoultramicroscopicsilicovolcanoconi
#define MIN_HIST_X 0
#define MAX_HIST_X LARGEST_ENGLISH_WORD
#define MIN_HIST_Y 0

int intmin(int a, int b) { return a < b ? a : b; }
int intmax(int a, int b) { return a > b ? a : b; }

// no longer needed since cap at word max
// int normalise(int x, int xMin, int xMax, int rangeMin, int rangeMax) {
//   int numerator = (x - xMin) * (rangeMax - rangeMin);
//   int denominator = (xMax - xMin);
//   return (numerator / denominator) + rangeMin;
// }

char *genstr(char c, int num) {
  static char str[100];
  int i;
  for (i = 0; i < num; i++) {
    str[i] = c;
  }
  str[i++] = '\0';
  return str;
}

int main() {
  char c;
  int nc, nw, state;
  int hist[MAX_HIST_X]; // index is num words up to maximum, value is
                        // num words
  const struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  const int LINES =
      w.ws_row - 4; // negative offset for the ui elements; ie graph x axis

  // SETUP
  int minnc = 2147483647;
  int maxnc = 0;
  for (int i = 0; i < MAX_HIST_X; i++) {
    hist[i] = 0;
  }
  state = OUT;
  nw = nc = 0;

  char teststr[] =
      "1 22 22 333 333 333 4444 4444 4444 4444 55555 55555 55555 "
      "55555 55555 666666 666666 666666 666666 666666 666666 "
      "7777777 7777777 7777777 7777777 7777777 7777777 7777777 88888888 "
      "88888888 88888888 88888888 88888888 88888888 88888888 88888888 "
      "999999999 999999999 999999999 999999999 999999999 999999999 999999999 "
      "999999999 999999999 1010101010 1010101010 1010101010 1010101010 "
      "1010101010 1010101010 1010101010 1010101010 1010101010 1010101010 ";
  int i = 0;
  while ((c = teststr[i++])) {
    if (c == ' ' || c == '\n' || c == '\t') {
      // updates
      minnc = intmin(minnc, nc);
      maxnc = intmax(maxnc, nc);
      hist[intmin(nc - 1, MAX_HIST_X - 1)]++;

      nc = 0;
      state = OUT;
    } else if (state == OUT) {
      state = IN;
      nc = 1;
      ++nw;
    } else if (state == IN) {
      ++nc;
    }
  }

  // last saved
  minnc = intmin(minnc, nc);
  maxnc = intmax(maxnc, nc);
  hist[intmin(nc - 1, MAX_HIST_X - 1)]++; // add the last saved nc

  // GENERATE HISTOGRAM
  int hist_x, norm_x;
  fprintf(stdout, "   +%s+\n", genstr('-', MAX_HIST_X * 4 - 1));
  for (int row = LINES; row > 0; row--) {
    fprintf(stdout, "%2i |", row);
    for (int col = 0; col < MAX_HIST_X; col++) {
      hist_x = hist[col];
      if (row <= hist_x) {
        if (row == LINES) {
          fprintf(stdout, "%3i|",
                  hist_x); // value chopped off by vertical limit, show value
        } else {
          fprintf(stdout, " # |"); // value shown
        }
      } else {
        fprintf(stdout, "   |"); // value not shown
      }
    }
    fprintf(stdout, "\n");
  }
  fprintf(stdout, "   +%s+\n", genstr('-', MAX_HIST_X * 4 - 1));
  fprintf(stdout, "   ");
  for (int col = 1; col <= MAX_HIST_X; col++) {
    fprintf(stdout, " %2i ", col);
  }
  fprintf(stdout, "\n");

  return 1;
}
