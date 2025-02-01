#include <unistd.h>

// this function will read until the next newline character
// and save the characters in a string you provide in arg2
int read_until_nl(int fd, char line[]) {
  int i = 0;
  int ret_read = 0;
  while ((ret_read = read(fd, &line[i], 1))) {
    if (line[i] == '\n') {
      break;
    }
    i++;
  }
  return ret_read;
}

