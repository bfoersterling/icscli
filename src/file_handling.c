#include <fcntl.h>
#include <string.h>
#include <unistd.h>

// Reads from the open file descriptor fd until the next newline character.
// Saves the characters in "line".
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

// Searches for a string in a file from the current file position
// and saves all characters until that string in "buffer".
// The file position will be placed after the search_string.
// Not only truncates but fills remaining chars with null characters.
void read_until_string(int fd, char buffer[], char search_string[]) {
	int i = 0;
	size_t j = 0;

	while(read(fd, &buffer[i], 1)) {
		if (buffer[i] == search_string[j]) {
			j++;
		} else {
			j = 0;
		}
		if (j == (strlen(search_string))) {
			break;
		}
		i++;
	}
	size_t truncate_position = strlen(buffer) - strlen(search_string);
	memset(&buffer[truncate_position], '\0', truncate_position);
}

// Seeks for a string in an open file.
// It will place the file position AFTER ("_a") that string.
void seek_string_a(int fd, char search_string[]) {
	size_t j = 0;
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
