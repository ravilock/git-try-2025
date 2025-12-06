/*
 * dynamic array usage
 * declare a struct with the following format:
 * struct {
 *  int *items; <- this could be some other type
 *  size_t count;
 *  size_t capacity;
 * } Numbers;
 *
 * and use da_append passing the
 */

#define da_append(xs, x)                                                       \
  do {                                                                         \
    if (xs->count >= xs->capacity) {                                           \
      if (xs->capacity == 0) {                                                 \
        xs->capacity = 1;                                                      \
      } else {                                                                 \
        xs->capacity *= 2;                                                     \
      }                                                                        \
      xs->items = realloc(xs->items, xs->capacity * sizeof(*xs->items));       \
      if (xs->items == NULL) {                                                 \
        printf("Failed to da_append\n");                                       \
        exit(1);                                                               \
      }                                                                        \
    }                                                                          \
    xs->items[xs->count++] = x;                                                \
  } while (0)
