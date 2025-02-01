// this function will seek for a string in an open file
// it will place the file position AFTER that string

#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void seek_string_a(int fd, char search_string[]) {
  int j = 0;
  char char_reader = '\0';

  while(read(fd, &char_reader, 1)) {
    if (char_reader == search_string[j]) {
      j++;
    } else {
      j = 0;
    }
    if (j == (strlen(search_string))) {
      break;
    }
  }
}
