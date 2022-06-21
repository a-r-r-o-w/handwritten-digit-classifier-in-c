#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mnist.h"
#include "nn.h"

int main () {
  srand(time(0));

  mnist_t dataset;
  mnist_constructor(&dataset);
  mnist_load(&dataset);

  for (int i = 0; i < 10; ++i) {
    mnist_display_random_train_image(&dataset);
    puts("");
  }

  mnist_destructor(&dataset);

  return 0;
}
