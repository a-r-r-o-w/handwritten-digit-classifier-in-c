#include <math.h>

#include "utils.h"

long double sigmoid (long double x) {
  long double r = 1;
  r /= 1 + exp2l(-x);
  return r;
}

long double sigmoid_derivative (long double x) {
  long double r = sigmoid(x);
  return r * (1 - r);
}

long double square_error (long double x, long double y) {
  long double z = x - y;
  return z * z;
}

long double square_error_derivative (long double x, long double y) {
  return 2 * (x - y);
}
