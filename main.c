#include "./diff.h"
#include <stdio.h>

int main(int argc, char **argv) {
  int distance = 0;
  distance = dyn_lev("abc", "xy");
  printf("dyn_lev(abc, xy) = %d\n", distance);
  distance = lev("abc", "xy");
  printf("lev(abc, xy) = %d\n", distance);
  printf("---------------\n");
  printf("---------------\n");
  printf("---------------\n");
  printf("---------------\n");

  distance = dyn_lev("abc", "");
  printf("dyn_lev(abc, ) = %d\n", distance);
  distance = lev("abc", "");
  printf("lev(abc, ) = %d\n", distance);
  printf("---------------\n");
  printf("---------------\n");
  printf("---------------\n");
  printf("---------------\n");

  distance = dyn_lev("abc", "c");
  printf("dyn_lev(abc, c) = %d\n", distance);
  distance = lev("abc", "c");
  printf("lev(abc, c) = %d\n", distance);
  printf("---------------\n");
  printf("---------------\n");
  printf("---------------\n");
  printf("---------------\n");

  distance = dyn_lev("abc", "abd");
  printf("dyn_lev(abc, abd) = %d\n", distance);
  distance = lev("abc", "abd");
  printf("lev(abc, abd) = %d\n", distance);
  printf("---------------\n");
  printf("---------------\n");
  printf("---------------\n");
  printf("---------------\n");

  printf("lev(abcd, abd) = %d\n", distance);
  distance = dyn_lev("abcd", "abd");
  printf("dyn_lev(abcd, abd) = %d\n", distance);
  distance = lev("abcd", "abd");
  printf("lev(abcd, abd) = %d\n", distance);
  printf("---------------\n");
  printf("---------------\n");
  printf("---------------\n");
  printf("---------------\n");

  distance = dyn_lev("abcd", "abe");
  printf("dyn_lev(abcd, abe) = %d\n", distance);
  distance = lev("abcd", "abe");
  printf("lev(abcd, abe) = %d\n", distance);
  printf("---------------\n");
  printf("---------------\n");
  printf("---------------\n");
  printf("---------------\n");
  return 0;
}
