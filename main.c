#include "./diff.h"
#include <stdio.h>

int main(int argc, char **argv) {
  int distance = lev("abc", "abc");
  printf("lev(abc, abc) = %d\n", distance);
  distance = dyn_lev("abc", "abc");
  printf("dyn_lev(abc, abc) = %d\n", distance);
  printf("---------------\n");
  distance = lev("abc", "abd");
  printf("lev(abc, abd) = %d\n", distance);
  distance = dyn_lev("abc", "abd");
  printf("dyn_lev(abc, abd) = %d\n", distance);
  printf("---------------\n");
  distance = lev("abcd", "abd");
  printf("lev(abcd, abd) = %d\n", distance);
  distance = dyn_lev("abcd", "abd");
  printf("dyn_lev(abcd, abd) = %d\n", distance);
  printf("---------------\n");
  distance = lev("abcd", "abe");
  printf("lev(abcd, abe) = %d\n", distance);
  distance = dyn_lev("abcd", "abe");
  printf("dyn_lev(abcd, abe) = %d\n", distance);
  printf("---------------\n");
  return 0;
}
