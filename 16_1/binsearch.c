#include "binsearch.h"

size_t bin_place(const int *array, int el, size_t n) {
  const int *left = array;
  const int *right = array + n;

  while (left < right) {
    const int *mid = left + (right - left) / 2;
    if (*mid > el) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  return (size_t)(left - array);
}
