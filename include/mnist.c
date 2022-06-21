#include <stdio.h>
#include <stdlib.h>

#include "error_handler.h"
#include "matrix.h"
#include "mnist.h"

// Construct a mnist object and allocate necessary memory
void mnist_constructor (mnist_t* m) {
  m->train_size = TRAINING_DATASET_SIZE;
  m->test_size = TESTING_DATASET_SIZE;
  m->train_images = (matrix_t*)malloc(m->train_size * sizeof(matrix_t));
  m->test_images = (matrix_t*)malloc(m->test_size * sizeof(matrix_t));
  
  for (int i = 0; i < m->train_size; ++i)
    matrix_constructor(&m->train_images[i], 28, 28, 0);
  for (int i = 0; i < m->test_size; ++i)
    matrix_constructor(&m->test_images[i], 28, 28, 0);

  matrix_constructor(&m->train_labels, 1, m->train_size, 0);
  matrix_constructor(&m->test_labels, 1, m->test_size, 0);
}

// Destruct a mnist object and free up allocated memory
void mnist_destructor (mnist_t* m) {
  matrix_destructor(&m->test_labels);
  matrix_destructor(&m->train_labels);

  for (int i = 0; i < m->test_size; ++i)
    matrix_destructor(m->test_images + i);
  for (int i = 0; i < m->train_size; ++i)
    matrix_destructor(&m->train_images[i]);
  
  m->test_images = NULL;
  m->train_images = NULL;
  m->test_size = 0;
  m->train_size = 0;
}

// Display a mnist digit image
// Note that depending on the font used in the terminal and other terminal settings,
// the displayed image may vary in size and appearance
// The terminal you use must support ANSI Escape Codes
void mnist_display_image (matrix_t* img, int label) {
  printf("Label: %d\n", label);
  for (int i = 0; i < MNIST_IMAGE_HEIGHT; ++i) {
    for (int j = 0; j < MNIST_IMAGE_WIDTH; ++j) {
      int value = matrix_get(img, i, j);
      printf("\x1b[38;2;%d;%d;%dm  \x1b[0m", value, value, value);
    }
    puts("");
  }
}

// Display a mnist digit image from the testing dataset
void mnist_display_test_image (mnist_t* m, int index) {
  if (index >= m->test_size)
    error("out of bounds access for testing dataset");
  mnist_display_image(&m->test_images[index], m->test_labels.values[index]);
}

// Display a mnist digit image from the training dataset
void mnist_display_train_image (mnist_t* m, int index) {
  if (index >= m->train_size)
    error("out of bounds access for training dataset");
  mnist_display_image(&m->train_images[index], m->train_labels.values[index]);
}

// Display a random mnist digit image from the testing dataset
void mnist_display_random_test_image (mnist_t* m) {
  int r = rand() % m->test_size;
  mnist_display_image(&m->test_images[r], m->test_labels.values[r]);
}

// Display a random mnist digit image from the training dataset
void mnist_display_random_train_image (mnist_t* m) {
  int r = rand() % m->train_size;
  mnist_display_image(&m->train_images[r], m->train_labels.values[r]);
}

// Load the mnist dataset
void mnist_load (mnist_t* m) {
  char mnist_train[] = "../res/datasets/mnist_train.csv";
  char mnist_test[] = "../res/datasets/mnist_test.csv";
  
  // load the mnist training dataset
  {
    FILE* stream = fopen(mnist_train, "r");
    int value;
    
    // consume the first line with column names
    while (fgetc(stream) != '\n')
      continue;
    
    // read the mnist training dataset
    for (int i = 0; i < m->train_size; ++i) {
      // the first column contains the image label
      fscanf(stream, "%d,", &value);
      m->train_labels.values[i] = value;

      // the remaining columns contain image data
      for (int j = 0; j < MNIST_IMAGE_SIZE - 1; ++j) {
        fscanf(stream, "%d,", &value);
        m->train_images[i].values[j] = value;
      }
      fscanf(stream, "%d", &value);
      m->train_images[i].values[MNIST_IMAGE_SIZE - 1] = value;
    }

    fclose(stream);
  }

  // load the mnist testing dataset
  {
    FILE* stream = fopen(mnist_test, "r");
    int value;
    
    // consume the first line with column names
    while (fgetc(stream) != '\n')
      continue;
    
    // read the mnist testing dataset
    for (int i = 0; i < m->test_size; ++i) {
      // the first column contains the image label
      fscanf(stream, "%d,", &value);
      m->test_labels.values[i] = value;

      // the remaining columns contain image data
      for (int j = 0; j < MNIST_IMAGE_SIZE - 1; ++j) {
        fscanf(stream, "%d,", &value);
        m->test_images[i].values[j] = value;
      }
      fscanf(stream, "%d", &value);
      m->test_images[i].values[MNIST_IMAGE_SIZE - 1] = value;
    }

    fclose(stream);
  }
}
