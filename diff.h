#include <stddef.h>

#define IGNORE 'I'
#define REMOVE 'R'
#define ADD 'A'
#define SUBSTITUTE 'S'

typedef struct {
  int distance;
  char action;
} lev_char_distance;

typedef struct {
  lev_char_distance *items;
  size_t count;
  size_t capacity;
} dyn_lev_char_distance;

typedef struct {
  size_t rows;
  size_t cols;
  lev_char_distance **matrix;
} lev_distance;

lev_distance *lev(const char *a, const char *b);

void lev_trackdiff(lev_distance *distance);
