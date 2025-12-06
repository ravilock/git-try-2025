#include "./da_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int IGNORE = 0;
const int REMOVE = 1;
const int ADD = 2;
const int REPLACE = 3;

typedef struct {
  int action;
  int index;
} str_action;

void display_action(str_action action) {
  switch (action.action) {
  case 0:
    printf("IGNORE ");
    break;
  case 1:
    printf("REMOVE ");
    break;
  case 2:
    printf("ADD ");
    break;
  case 3:
    printf("REPLACE ");
    break;
  default:
    printf("UNKOWN %d ", action.action);
    exit(1);
  }
  printf("index %d\n", action.index);
}

typedef struct {
  str_action *items;
  size_t count;
  size_t capacity;
} str_actions;

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
    s_copy[i + 1] = '\0';
    s_prefixes[i] = s_copy;
  }
  return s_prefixes;
}

void display_distance_matrix(int **distance_matrix, const char *a,
                             const char *b) {
  int rows = strlen(a) + 1;
  int cols = strlen(b) + 1;
  printf("%s %s\n", a, b);
  printf("______________start\n");
  printf("- - ");
  for (int j = 0; j < cols - 1; j++) {
    printf("%c ", b[j]);
  }
  printf("\n");
  for (int i = 0; i < rows; i++) {
    if (i == 0) {
      printf("- ");
    } else {
      printf("%c ", a[i - 1]);
    }
    for (int j = 0; j < cols; j++) {
      printf("%d ", distance_matrix[i][j]);
    }
    printf("\n");
  }
  printf("______________end\n");
}

// a: abz
// b: xy
//
// result:
// - - x y
// - 0 1 2
// a 1 0 0
// b 2 0 0
// z 3 0 0

//
int **create_distance_matrix(const char *a, const char *b) {
  int **distances_matrix;
  int *distances;
  int a_len = strlen(a);
  int b_len = strlen(b);
  distances_matrix = malloc(sizeof(int *) * (a_len + 1));
  if (distances_matrix == NULL) {
    printf("distances_matrix is NULL\n");
    exit(69);
  }
  for (int i = 0; i < (a_len + 1); i++) {
    int *distances = malloc(sizeof(int) * (b_len + 1));
    if (distances == NULL) {
      printf("distances is NULL\n");
      exit(69);
    }
    distances_matrix[i] = distances;
    for (int j = 0; j < (b_len + 1); j++) {
      if (i == 0) {
        distances_matrix[0][j] = j;
      } else if (j == 0) {
        distances_matrix[i][0] = i;
      } else {
        distances_matrix[i][j] = 0;
      }
    }
  }
  // display_distance_matrix(distances_matrix, a, b);
  return distances_matrix;
}

int dyn_lev(const char *a, const char *b) {
  int cost;
  if (strlen(a) == 0) {
    return strlen(b);
  }
  if (strlen(b) == 0) {
    return strlen(a);
  }
  int distance = 0;
  int rows = strlen(a) + 1;
  int cols = strlen(b) + 1;
  int **distances = create_distance_matrix(a, b);
  int substitution_cost;
  int i = 0;
  int j = 0;
  for (j = 1; j < cols; j++) {
    for (i = 1; i < rows; i++) {
      if (a[i - 1] == b[j - 1]) {
        substitution_cost = 0;
      } else {
        substitution_cost = 1;
      }
      int ain_b = distances[i - 1][j] + 1;
      int a_bin = distances[i][j - 1] + 1;
      int in = distances[i - 1][j - 1] + substitution_cost;
      if (ain_b < a_bin) {
        cost = ain_b;
      } else {
        cost = a_bin;
      }
      if (in < cost) {
        cost = in;
      }
      distances[i][j] = cost;
      // display_distance_matrix(distances, a, b);
    }
  }
  distance = distances[i - 1][j - 1];
  free(distances);
  return distance;
}
