#include "./diff.h"
#include "./da_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display_lev_distance_matrix(lev_distance **distance_matrix, const char *a,
                                 const char *b) {
  int rows = strlen(a) + 1;
  int cols = strlen(b) + 1;
  printf("---------------\n");
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
      if (distance_matrix[i][j].action != '\0') {
        printf("(%c) ", distance_matrix[i][j].action);
      } else {
        printf("(?) ");
      }
    }
    printf("\n");
  }
  printf("---------------\n");
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
      if (i == 0 && j == 0) {
        distances_matrix[i][j].distance = 0;
        distances_matrix[i][j].action = IGNORE;
      } else if (i == 0) {
        distances_matrix[i][j].distance = j;
        distances_matrix[i][j].action = ADD;
      } else if (j == 0) {
        distances_matrix[i][j].distance = i;
        distances_matrix[i][j].action = ADD;
      }
    }
  }
  display_lev_distance_matrix(distances_matrix, a, b);
  return distances_matrix;
}

lev_distance **lev(const char *a, const char *b) {
  int cost, substitution_probe_cost, add_cost, remove_cost, substitution_cost;
  int rows = strlen(a) + 1;
  int cols = strlen(b) + 1;
  lev_distance **distances = create_distance_matrix(a, b);
  for (int j = 1; j < cols; j++) {
    for (int i = 1; i < rows; i++) {
      if (a[i - 1] == b[j - 1]) {
        substitution_probe_cost = 0;
      } else {
        substitution_probe_cost = 1;
      }
      remove_cost = distances[i - 1][j].distance + 1; // REMOVE
      add_cost = distances[i][j - 1].distance + 1;    // ADD
      substitution_cost = substitution_probe_cost +
                          distances[i - 1][j - 1].distance; // SUBSTITUTE
      if (remove_cost < add_cost) {
        cost = remove_cost;
        distances[i][j].action = REMOVE;
      } else {
        cost = add_cost;
        distances[i][j].action = ADD;
      }
      if (substitution_cost < cost) {
        cost = substitution_cost;
        if (substitution_probe_cost == 1) {
          distances[i][j].action = SUBSTITUTE;
        } else {
          distances[i][j].action = IGNORE;
        }
      }
      distances[i][j].distance = cost;
    }
  }
  display_lev_distance_matrix(distances, a, b);
  return distances;
}
