#include "./da_array.h"
#include "./diff.h"
#include <stdio.h>

int main(int argc, char **argv) {
  int distance = 0;
  distance = lev("abc", "xy");
  printf("lev(abc, xy) = %d\n", distance);
  printf("---------------\n");
  printf("---------------\n");

  distance = lev("abc", "");
  printf("lev(abc, ) = %d\n", distance);
  printf("---------------\n");
  printf("---------------\n");

  distance = lev("abc", "c");
  printf("lev(abc, c) = %d\n", distance);
  printf("---------------\n");
  printf("---------------\n");

  distance = lev("abc", "abd");
  printf("lev(abc, abd) = %d\n", distance);
  printf("---------------\n");
  printf("---------------\n");

  distance = lev("abcd", "abd");
  printf("lev(abcd, abd) = %d\n", distance);
  printf("---------------\n");
  printf("---------------\n");

  distance = lev("abcd", "abe");
  printf("lev(abcd, abe) = %d\n", distance);
  printf("---------------\n");
  printf("---------------\n");

  distance = lev("apple", "appled");
  printf("lev(apple, appled) = %d\n", distance);
  printf("---------------\n");
  printf("---------------\n");

  distance = lev("appled", "apple");
  printf("lev(appled, apple) = %d\n", distance);
  printf("---------------\n");
  printf("---------------\n");
  return 0;
}
