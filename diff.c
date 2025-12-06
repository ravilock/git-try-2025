#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}

int lev(const char *a, const char *b) {
  int a_len = strlen(a);
  int b_len = strlen(b);
  if (b_len == 0) {
    return a_len;
  }
  if (a_len == 0) {
    return b_len;
  }
  if (a[0] == b[0]) {
    return lev(++a, ++b);
  }
  int atail_b = lev(a + 1, b);
  int a_btail = lev(a, b + 1);
  int tails = lev(a + 1, b + 1);
  return 1 + min(min(atail_b, a_btail), tails);
}

int sum_sequence(int a, int b) {
  int pair_sum = (a + b);
  return (pair_sum * (b - a + 1)) / 2;
}

char **create_prefixes(const char *s) {
  int s_len = strlen(s);
  char **s_prefixes;
  char *s_copy;
  s_prefixes = malloc(s_len * sizeof(char));
  if (s_prefixes == NULL) {
    printf("s_prefixes is NULL\n");
    exit(69);
  }
  for (int i = 0; i < s_len; i++) {
    s_copy = malloc((s_len + 1) * sizeof(char));
    if (s_copy == NULL) {
      printf("s_copy is NULL\n");
      exit(69);
    }
    strcpy(s_copy, s);
    s_copy[s_len - i] = '\0';
    s_prefixes[i] = s_copy;
  }
  return s_prefixes;
}

int dyn_lev(const char *a, const char *b) {
  int distance = 0;
  int a_len = strlen(a);
  int b_len = strlen(b);
  char **a_prefixes = create_prefixes(a);
  char **b_prefixes = create_prefixes(b);
  int ai = 0;
  int aj = 0;
  int bi = 0;
  int bj = 0;

  while (1) {
    char *a_s = a_prefixes[ai];
    char *b_s = b_prefixes[bi];
    if (a_s[aj] == b_s[bj]) {
      aj++;
      bj++;
    } else {
      ai++;
      aj = 0;
      bj = 0;
      continue;
    }
    if (a_s[aj] == '\0') {
      free(a_prefixes);
      free(b_prefixes);
      return distance + strlen(&b_s[bj]);
    }
    if (b_s[bj] == '\0') {
      free(a_prefixes);
      free(b_prefixes);
      return distance + strlen(&a_s[aj]);
    }
  }
  free(a_prefixes);
  free(b_prefixes);
  return distance;
}
