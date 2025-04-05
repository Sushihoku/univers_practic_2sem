#include "binsearch.h"
#include <stdio.h>

void test(const int *array, size_t size, int el, size_t expected) {
  size_t result = bin_place(array, el, size);
  printf("result: %2zu %s\n", result, result == expected ? "PASS" : "FAIL");
}

int main() {
  const int a[] = {1, 2, 3, 3, 3, 4, 5, 5, 5, 6, 6};
  size_t n = sizeof(a) / sizeof(a[0]);

  printf("Тесты\n");
  test(a, n, -1, 0);
  test(a, n, 0, 0);
  test(a, n, 1, 1);
  test(a, n, 2, 2);
  test(a, n, 3, 5);
  test(a, n, 4, 6);
  test(a, n, 5, 9);
  test(a, n, 6, 11);
  test(a, n, 7, 11);
  test(a, n, 8, 11);

  const int odd_repeat[] = {1, 2, 4, 4, 4, 4, 9};
  size_t nodd = sizeof(odd_repeat) / sizeof(odd_repeat[0]);
  test(odd_repeat, nodd, 4, 6);
  test(odd_repeat, nodd, 3, 2);
  test(odd_repeat, nodd, 10, 7);

  return 0;
}
