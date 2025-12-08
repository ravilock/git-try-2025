#include "./da_array.h"
#include "./diff.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  lev_distance *distance = 0;
  distance = lev("abc", "xy");
  printf("lev(abc, xy)\n");
  free(distance);

  distance = lev("abc", "");
  printf("lev(abc, )\n");

  distance = lev("abc", "c");
  printf("lev(abc, c)\n");

  distance = lev("abc", "abd");
  printf("lev(abc, abd)\n");

  distance = lev("abcd", "abd");
  printf("lev(abcd, abd)\n");

  distance = lev("abcd", "abe");
  printf("lev(abcd, abe)\n");

  distance = lev("apple", "appled");
  printf("lev(apple, appled)\n");

  distance = lev("appled", "apple");
  printf("lev(appled, apple)\n");

  distance = lev("hello", "hallow");
  printf("lev(hello, hallow)\n");
  return 0;
}
