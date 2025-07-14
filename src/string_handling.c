#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Cut a string into two parts separated by "delimiter".
// Choose the first part ("side"=0) or the second part ("side"=1).
// The chosen part will overwrite the original string "my_string".
void cut_string(char my_string[], char delimiter, int side) {
	char part1[256] = "";
	char part2[256] = "";

	bool split = false;

	int j = 0;
	for (size_t i = 0; i < strlen(my_string); i++) {
		if (my_string[i] == delimiter) {
			if (!split) {
				split = true;
				continue;
			}
		}

		if (!split) {
			part1[i] = my_string[i];
		} else {
			part2[j] = my_string[i];
			j++;
		}
	}

	memset(my_string, '\0', strlen(my_string));
	if (side == 0) {
		strcpy(my_string, part1);
	} else {
		strcpy(my_string, part2);
	}
}

// Removes all new lines and carriage returns from a string.
void remove_nl_and_cr(char raw_string[]) {
	char processed_string[strlen(raw_string)];

	// counter for num of elements of processed_string
	int j = 0;
	for (size_t i = 0; i < strlen(raw_string); i++) {
		if (raw_string[i] == '\n' || raw_string[i] == '\r') {
			continue;
		} else {
			processed_string[j] = raw_string[i];
			j++;
		}
	}
	processed_string[j] = '\0';

	memset(raw_string, '\0', strlen(raw_string));
	strcpy(raw_string, processed_string);
}

void remove_until_delim(char raw_string[], char delimiter, int occurence) {
	int chunk = 0;
	int j = 0;
	char *tmp_string = malloc(strlen(raw_string));
	memset(tmp_string, '\0', strlen(raw_string));

	for (size_t i = 0; i < strlen(raw_string); i++) {
		if (raw_string[i] == delimiter) {
			chunk++;
		}
		if (chunk >= occurence) {
			tmp_string[j] = raw_string[i];
			j++;
		}
	}
	strcpy(raw_string, tmp_string);
	free(tmp_string);
}

// Removes new lines, carriage returns and spaces from "raw_string".
// TODO: Use isspace from ctype.h.
void remove_whitespace(char raw_string[]) {
	char processed_string[strlen(raw_string)];

	// counter for num of elements of processed_string
	int j = 0;
	for (size_t i = 0; i < strlen(raw_string); i++) {
		if (raw_string[i] == '\n' || raw_string[i] == '\r' \
				|| raw_string[i] == ' ') {
			continue;
		} else {
			processed_string[j] = raw_string[i];
			j++;
		}
	}
	processed_string[j] = '\0';

	memset(raw_string, '\0', strlen(raw_string));
	strcpy(raw_string, processed_string);
}


// Removes all whitespace from the left side of a string.
void trim_left(char* input) {
	int pos = 0;

	while(isspace(input[pos])) {
		pos++;
	}

	memmove(input, input + pos, strlen(input) + 1);
}

// Removes all whitespace from the right side of a string.
void trim_right(char* input) {
	int pos = strlen(input) - 1;

	// reading a negative index is undefined behavior
	while(pos >= 0 && isspace(input[pos])) {
		pos--;
	}

	input[pos+1] = '\0';
}

// Removes all whitespace from the left and right side of a string.
void trim_space(char* input) {
	trim_left(input);
	trim_right(input);
}
