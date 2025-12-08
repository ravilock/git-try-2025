#define IGNORE 'I'
#define REMOVE 'R'
#define ADD 'A'
#define SUBSTITUTE 'S'

typedef struct {
  int distance;
  char action;
} lev_distance;

lev_distance **lev(const char *a, const char *b);
