#include "allocator.h"
#include "internal.h"
#include <stdint.h>
#include <stdio.h>

#define CHECK(cond, msg)                                                       \
  if (!(cond)) {                                                               \
    printf("❌ FAIL: %s\n", msg);                                              \
    return 1;                                                                  \
  } else {                                                                     \
    printf("✔ %s\n", msg);                                                     \
  }

int main() {

  printf("=== BASIC MALLOC TEST ===\n");

  void *a = my_malloc(16);
  void *b = my_malloc(32);
  void *c = my_malloc(24);

  CHECK(a && b && c, "malloc returned non-null");

  printf("a=%p b=%p c=%p\n", a, b, c);

  CHECK(a != b && b != c && a != c, "pointers are distinct");

  // alignment check
   CHECK(((uintptr_t)a % ALIGNMENT) == 0, "a aligned");
   CHECK(((uintptr_t)b % ALIGNMENT) == 0, "b aligned");
   CHECK(((uintptr_t)c % ALIGNMENT) == 0, "c aligned");

  printf("\n=== FREE + COALESCE TEST ===\n");

  my_free(b);
  my_free(a);

  // połączenie a+b
  void *d = my_malloc(40);
  printf("d=%p\n", d);

  CHECK(d == a, "coalesce + reuse works (a+b)");

  printf("\n=== EDGE CASES ===\n");

  void *zero = my_malloc(0);
  CHECK(zero == NULL, "malloc(0) == NULL");

  my_free(NULL);
  CHECK(1, "free(NULL) safe");

  printf("\n=== SPLIT TEST ===\n");

  void *x = my_malloc(128);
  my_free(x);

  void *y = my_malloc(32);
  void *z = my_malloc(32);

  CHECK(y != NULL && z != NULL, "split works");

  printf("y=%p z=%p\n", y, z);

  printf("\n=== STRESS TEST ===\n");

  void *arr[50];

  for (int i = 0; i < 50; i++) {
    arr[i] = my_malloc(8 + i * 3);
    CHECK(arr[i] != NULL, "stress malloc");
  }

  for (int i = 0; i < 50; i++) {
    my_free(arr[i]);
  }

  printf("✔ stress free\n");

  printf("\n=== FULL COALESCE TEST ===\n");

  void *p1 = my_malloc(32);
  void *p2 = my_malloc(32);
  void *p3 = my_malloc(32);

  my_free(p2);
  my_free(p1);
  my_free(p3);

  void *big = my_malloc(80);
  CHECK(big == p1, "full coalesce (3 blocks merged)");

  printf("\n=== LARGE ALLOCATION TEST ===\n");

  void *big2 = my_malloc(5000);
  CHECK(big2 != NULL, "large allocation works");

  printf("\n=== OVERLAP TEST ===\n");

  void *o1 = my_malloc(32);
  void *o2 = my_malloc(32);

  CHECK((char *)o1 + 32 <= (char *)o2 || (char *)o2 + 32 <= (char *)o1,
        "no overlap");

  printf("\n=== HEADER/FOOTER CONSISTENCY ===\n");

  CHECK(GET(HDRP(o1)) == GET(FTRP(o1)), "header == footer (o1)");
  CHECK(GET(HDRP(o2)) == GET(FTRP(o2)), "header == footer (o2)");

  printf("\n=== ALL TESTS PASSED 🚀 ===\n");

  return 0;
}