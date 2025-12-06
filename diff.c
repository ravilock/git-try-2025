#include "./da_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char IGNORE = 'I';
const char REMOVE = 'R';
const char ADD = 'A';
const char SUBSTITUTE = 'S';

typedef struct {
  char action;
  int index;
} str_action;

typedef struct {
  str_action *items;
  size_t count;
  size_t capacity;
} str_actions;

typedef struct {
  int distance;
  str_action str_action;
} lev_distance;

void display_lev_distance_matrix(lev_distance **distance_matrix, const char *a,
                                 const char *b) {
  int rows = strlen(a) + 1;
  int cols = strlen(b) + 1;
  printf("%s %s\n", a, b);
  printf("______________start\n");
  printf("-     ");
  printf("-     ");
  for (int j = 0; j < cols - 1; j++) {
    printf("%c     ", b[j]);
  }
  printf("\n");
  for (int i = 0; i < rows; i++) {
    if (i == 0) {
      printf("-     ");
    } else {
      printf("%c     ", a[i - 1]);
    }
    for (int j = 0; j < cols; j++) {
      printf("%d ", distance_matrix[i][j].distance);
      if (distance_matrix[i][j].str_action.action != '\0') {
        printf("(%c) ", distance_matrix[i][j].str_action.action);
      } else {
        printf("(%c) ", IGNORE);
      }
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
lev_distance **create_distance_matrix(const char *a, const char *b) {
  lev_distance **distances_matrix;
  int *distances;
  int a_len = strlen(a);
  int b_len = strlen(b);
  distances_matrix = malloc(sizeof(lev_distance *) * (a_len + 1));
  if (distances_matrix == NULL) {
    printf("distances_matrix is NULL\n");
    exit(69);
  }
  for (int i = 0; i < (a_len + 1); i++) {
    lev_distance *distances = malloc(sizeof(lev_distance) * (b_len + 1));
    if (distances == NULL) {
      printf("distances is NULL\n");
      exit(69);
    }
    distances_matrix[i] = distances;
    for (int j = 0; j < (b_len + 1); j++) {
      if (i == 0) {
        distances_matrix[0][j].distance = j;
      } else if (j == 0) {
        distances_matrix[i][0].distance = i;
      } else {
        distances_matrix[i][j].distance = 0;
      }
    }
  }
  return distances_matrix;
}

int lev(const char *a, const char *b) {
  int cost;
  str_action used_action;
  if (strlen(a) == 0) {
    return strlen(b);
  }
  if (strlen(b) == 0) {
    return strlen(a);
  }
  int distance = 0;
  int rows = strlen(a) + 1;
  int cols = strlen(b) + 1;
  lev_distance **distances = create_distance_matrix(a, b);
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
      int ain_b = distances[i - 1][j].distance + 1; // REMOVE
      int a_bin = distances[i][j - 1].distance + 1; // ADD
      int in =
          distances[i - 1][j - 1].distance + substitution_cost; // SUBSTITUTE
      if (ain_b < a_bin) {
        cost = ain_b;
        used_action.action = REMOVE;
      } else {
        cost = a_bin;
        used_action.action = ADD;
      }
      if (in < cost) {
        cost = in;
        if (substitution_cost == 1) {
          used_action.action = SUBSTITUTE;
        } else {
          used_action.action = IGNORE;
        }
      }
      distances[i][j].distance = cost;
      distances[i][j].str_action = used_action;
    }
  }
  display_lev_distance_matrix(distances, a, b);
  distance = distances[i - 1][j - 1].distance;
  free(distances);
  return distance;
}
