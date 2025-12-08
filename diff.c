#include "./diff.h"
#include "./da_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void display_lev_distance_matrix(lev_distance *distance, const char *a,
                                 const char *b) {
  printf("---------------\n");
  printf("-     ");
  printf("-     ");
  for (size_t j = 0; j < distance->cols - 1; j++) {
    printf("%c     ", b[j]);
  }
  printf("\n");
  for (size_t i = 0; i < distance->rows; i++) {
    if (i == 0) {
      printf("-     ");
    } else {
      printf("%c     ", a[i - 1]);
    }
    for (size_t j = 0; j < distance->cols; j++) {
      printf("%d ", distance->matrix[i][j].distance);
      if (distance->matrix[i][j].action != '\0') {
        printf("(%c) ", distance->matrix[i][j].action);
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
lev_distance *create_distance_matrix(const char *a, const char *b) {
  lev_distance *distance;
  lev_char_distance **matrix;
  lev_char_distance *distances;
  size_t a_len = strlen(a);
  size_t b_len = strlen(b);
  distance = malloc(sizeof(lev_distance));
  if (distance == NULL) {
    printf("distance is NULL\n");
    exit(69);
  }
  distance->rows = a_len + 1;
  distance->cols = b_len + 1;
  matrix = malloc(sizeof(lev_char_distance *) * (a_len + 1));
  if (matrix == NULL) {
    printf("distances_matrix is NULL\n");
    exit(69);
  }
  distance->matrix = matrix;
  for (size_t i = 0; i < (a_len + 1); i++) {
    distances = malloc(sizeof(lev_char_distance) * (b_len + 1));
    if (distances == NULL) {
      printf("distances is NULL\n");
      exit(69);
    }
    matrix[i] = distances;
    for (size_t j = 0; j < (b_len + 1); j++) {
      if (i == 0 && j == 0) {
        matrix[i][j].distance = 0;
        matrix[i][j].action = IGNORE;
      } else if (i == 0) {
        matrix[i][j].distance = j;
        matrix[i][j].action = ADD;
      } else if (j == 0) {
        matrix[i][j].distance = i;
        matrix[i][j].action = ADD;
      }
    }
  }
  return distance;
}

lev_distance *lev(const char *a, const char *b) {
  int cost, substitution_probe_cost, add_cost, remove_cost, substitution_cost;
  size_t rows = strlen(a) + 1;
  size_t cols = strlen(b) + 1;
  lev_distance *distances = create_distance_matrix(a, b);
  display_lev_distance_matrix(distances, a, b);
  for (size_t j = 1; j < cols; j++) {
    for (size_t i = 1; i < rows; i++) {
      if (a[i - 1] == b[j - 1]) {
        substitution_probe_cost = 0;
      } else {
        substitution_probe_cost = 1;
      }
      remove_cost = distances->matrix[i - 1][j].distance + 1; // REMOVE
      add_cost = distances->matrix[i][j - 1].distance + 1;    // ADD
      substitution_cost =
          substitution_probe_cost +
          distances->matrix[i - 1][j - 1].distance; // SUBSTITUTE
      if (remove_cost < add_cost) {
        cost = remove_cost;
        distances->matrix[i][j].action = REMOVE;
      } else {
        cost = add_cost;
        distances->matrix[i][j].action = ADD;
      }
      if (substitution_cost < cost) {
        cost = substitution_cost;
        if (substitution_probe_cost == 1) {
          distances->matrix[i][j].action = SUBSTITUTE;
        } else {
          distances->matrix[i][j].action = IGNORE;
        }
      }
      distances->matrix[i][j].distance = cost;
    }
  }
  display_lev_distance_matrix(distances, a, b);
  return distances;
}

void lev_trackdiff(lev_char_distance **matrix) {}
