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
lev_distance *create_lev_distance_matrix(const char *a, const char *b) {
  lev_distance *distance;
  lev_char_distance **matrix;
  lev_char_distance *distances;
  distance = malloc(sizeof(lev_distance));
  if (distance == NULL) {
    printf("distance is NULL\n");
    exit(69);
  }
  distance->rows = strlen(a) + 1;
  distance->cols = strlen(b) + 1;
  matrix = malloc(sizeof(lev_char_distance *) * (distance->rows));
  if (matrix == NULL) {
    printf("distances_matrix is NULL\n");
    exit(69);
  }
  distance->matrix = matrix;
  for (size_t i = 0; i < (distance->rows); i++) {
    distances = malloc(sizeof(lev_char_distance) * (distance->cols));
    if (distances == NULL) {
      printf("distances is NULL\n");
      exit(69);
    }
    matrix[i] = distances;
    for (size_t j = 0; j < (distance->cols); j++) {
      if (i == 0 && j == 0) {
        matrix[i][j].distance = 0;
        matrix[i][j].action = IGNORE;
      } else if (i == 0) {
        matrix[i][j].distance = j;
        matrix[i][j].action = ADD;
      } else if (j == 0) {
        matrix[i][j].distance = i;
        matrix[i][j].action = REMOVE;
      } else {
        matrix[i][j].distance = 0;
      }
    }
  }
  return distance;
}

void display_dyn_lev_char_distance(dyn_lev_char_distance *distances) {
  printf("count: %zu, capacity: %zu\n", distances->count, distances->capacity);
  for (size_t i = 0; i < distances->count; i++) {
    printf("(%d, %c) - ", distances->items[i].distance,
           distances->items[i].action);
  }
  printf("\n");
}

// returns a matrix representing the levenshtein distance between 'a' and 'b'
// 'b' can not be an empty string
lev_distance *lev(const char *a, const char *b) {
  int add_cost, remove_cost, substitute_cost;
  lev_distance *distances = create_lev_distance_matrix(a, b);
#ifdef LEV_TRACE
  display_lev_distance_matrix(distances, a, b);
#endif
  for (size_t j = 1; j < distances->cols; j++) {
    for (size_t i = 1; i < distances->rows; i++) {
      if (a[i - 1] == b[j - 1]) {
        distances->matrix[i][j].distance =
            distances->matrix[i - 1][j - 1].distance;
        distances->matrix[i][j].action = IGNORE;
        continue;
      }

      remove_cost = distances->matrix[i - 1][j].distance;         // REMOVE
      add_cost = distances->matrix[i][j - 1].distance;            // ADD
      substitute_cost = distances->matrix[i - 1][j - 1].distance; // SUBSTITUTE

      distances->matrix[i][j].distance = remove_cost;
      distances->matrix[i][j].action = REMOVE;
      if (distances->matrix[i][j].distance > add_cost) {
        distances->matrix[i][j].distance = add_cost;
        distances->matrix[i][j].action = ADD;
      }
      if (distances->matrix[i][j].distance > substitute_cost) {
        distances->matrix[i][j].distance = substitute_cost;
        distances->matrix[i][j].action = SUBSTITUTE;
      }

      distances->matrix[i][j].distance++;
    }
  }
#ifdef LEV_TRACE
  display_lev_distance_matrix(distances, a, b);
#endif
  return distances;
}

dyn_lev_char_distance *lev_trackdiff(lev_distance *distance) {
  lev_char_distance current_char_distance;
  dyn_lev_char_distance *lev_track = malloc(sizeof(dyn_lev_char_distance));
  if (lev_track == NULL) {
    printf("lev_track is NULL\n");
    exit(69);
  }
  dyn_lev_char_distance *rev_lev_track = malloc(sizeof(dyn_lev_char_distance));
  if (rev_lev_track == NULL) {
    printf("rev_lev_track is NULL\n");
    exit(69);
  }
  int rows = distance->rows - 1;
  int cols = distance->cols - 1;

  while (rows > 0 || cols > 0) {
    current_char_distance = distance->matrix[rows][cols];
    switch (current_char_distance.action) {
    case IGNORE:
      rows--;
      cols--;
      break;
    case SUBSTITUTE:
      rows--;
      cols--;
      break;
    case REMOVE:
      rows--;
      break;
    case ADD:
      cols--;
      break;
    default:
      printf("Unreachable\n");
      exit(1);
    }
    da_append(rev_lev_track, current_char_distance);
  }
  da_revert(rev_lev_track, lev_track);
#ifdef LEV_TRACE
  display_dyn_lev_char_distance(lev_track);
#endif
  return lev_track;
}

str_diff *diff(const char *a, const char *b) {
  lev_char_distance char_distance;
  char_diff cdiff;
  size_t a_len = strlen(a);
  size_t b_len = strlen(b);
  lev_distance *distance = lev(a, b);
  dyn_lev_char_distance *lev_track = lev_trackdiff(distance);
  str_diff *diff_result = malloc(sizeof(str_diff));
  if (diff_result == NULL) {
    printf("diff_result is NULL\n");
    exit(69);
  }
  for (size_t i = 0; i < lev_track->count; i++) {
    cdiff.action = lev_track->items[i].action;
    switch (cdiff.action) {
    case IGNORE:
      cdiff.from = a[i];
      cdiff.to = 0;
      break;
    case SUBSTITUTE:
      cdiff.from = a[i];
      cdiff.to = b[i];
      break;
    case REMOVE:
      cdiff.from = a[i];
      cdiff.to = 0;
      break;
    case ADD:
      cdiff.from = 0;
      cdiff.to = b[i];
      break;
    }
    da_append(diff_result, cdiff);
  }
  return diff_result;
}

void display_diff(str_diff *d) {
  printf("len - %zu\n", d->count);
  for (size_t i = 0; i < d->count; i++) {
    if (d->items[i].action == ADD) {
      printf("  ");
      continue;
    }
    printf("%c ", d->items[i].from);
  }
  printf("\n");
  for (size_t i = 0; i < d->count; i++) {
    switch (d->items[i].action) {
    case IGNORE:
      printf("  ");
      break;
    case SUBSTITUTE:
      printf("~ ");
      break;
    case REMOVE:
      printf("- ");
      break;
    case ADD:
      printf("+ ");
      break;
    }
  }
  printf("\n");
  for (size_t i = 0; i < d->count; i++) {
    if (d->items[i].action == REMOVE || d->items[i].action == IGNORE) {
      printf("  ");
      continue;
    }
    printf("%c ", d->items[i].to);
  }
  printf("\n");
  printf("\n");
}
