#ifndef HDC_ERROR_HANDLER_H
#define HDC_ERROR_HANDLER_H

#include <stdio.h>
#include <stdlib.h>

#define error(message) handle_verbose_error(__FILE__, __PRETTY_FUNCTION__, __LINE__, message)

void handle_error (const char* message) {
  fprintf(stderr, "Unfortunately, an error has occurred!\n%s", message);
  exit(EXIT_FAILURE);
}

void handle_verbose_error (const char* file_name, const char* function_name, int line_number, const char* message) {
  fprintf(stderr, "Unfortunately, an error has occurred!\n"
                  "    File: %s\n"
                  "Function: %s\n"
                  "    Line: %d\n"
                  " Message: %s\n",
    file_name, function_name, line_number, message
  );
  exit(EXIT_FAILURE);
}

#endif // HDC_ERROR_HANDLER_H
