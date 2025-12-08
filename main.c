#include "./da_array.h"
#include "./diff.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  lev_distance *distance;
  distance = lev("xy", "xyz");
  printf("lev(xy, xyz)\n");
  lev_trackdiff(distance);
  free(distance);

  distance = lev("abc", "xy");
  printf("lev(abc, xy)\n");
  lev_trackdiff(distance);
  free(distance);

  distance = lev("", "abc");
  printf("lev(, abc)\n");
  lev_trackdiff(distance);
  free(distance);

  distance = lev("abc", "c");
  printf("lev(abc, c)\n");
  lev_trackdiff(distance);
  free(distance);

  distance = lev("abc", "abd");
  printf("lev(abc, abd)\n");
  lev_trackdiff(distance);
  free(distance);

  distance = lev("abcd", "abd");
  printf("lev(abcd, abd)\n");
  lev_trackdiff(distance);
  free(distance);

  distance = lev("abcd", "abe");
  printf("lev(abcd, abe)\n");
  lev_trackdiff(distance);
  free(distance);

  distance = lev("apple", "appled");
  printf("lev(apple, appled)\n");
  lev_trackdiff(distance);
  free(distance);

  distance = lev("appled", "apple");
  printf("lev(appled, apple)\n");
  lev_trackdiff(distance);
  free(distance);

  distance = lev("hello", "hallow");
  printf("lev(hello, hallow)\n");
  lev_trackdiff(distance);
  free(distance);
  return 0;
}
