#include "./da_array.h"
#include "./diff.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  str_diff *diff_result;

  diff_result = diff("xy", "xyz");
  display_diff(diff_result);
  free(diff_result);

  diff_result = diff("abc", "xy");
  display_diff(diff_result);
  free(diff_result);

  diff_result = diff("", "abc");
  display_diff(diff_result);
  free(diff_result);

  diff_result = diff("abc", "c");
  display_diff(diff_result);
  free(diff_result);

  diff_result = diff("abc", "abd");
  display_diff(diff_result);
  free(diff_result);

  diff_result = diff("abcd", "abd");
  display_diff(diff_result);
  free(diff_result);

  diff_result = diff("abcd", "abe");
  display_diff(diff_result);
  free(diff_result);

  diff_result = diff("apple", "appled");
  display_diff(diff_result);
  free(diff_result);

  diff_result = diff("cppled", "aapple");
  display_diff(diff_result);
  free(diff_result);

  diff_result = diff("hello", "hallow");
  display_diff(diff_result);
  free(diff_result);
  return 0;
}
