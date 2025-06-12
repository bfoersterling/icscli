// the same as read_until_string, but this function not only truncates but fills remaining chars with null characters
// this function is cleaner and nicer to work with, but not as fast as "read_until_string"
// ct means "clean truncate"
// return 1 on success, -1 when buffer is NULL

#include <unistd.h>
#include <string.h>

void read_until_string(int fd, char buffer[], char search_string[]) {
	int i = 0;
	int j = 0;

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
