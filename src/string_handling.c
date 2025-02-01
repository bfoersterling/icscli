// cut a string into two parts by the first occurence of delimiter
// and choose the first part (side 0) or the second part (side 1)
// the chosen part will overwrite the original string

// cut a string into two parts by delimiter
// and choose the first part (side 0) or the second part (side 1)
// the chosen part will overwrite the original string

#include <string.h>
#include <stdlib.h>

void cut_string(char my_string[], char delimiter, int side) {
	char part1[256] = "";
	char part2[256] = "";

	int split = 0;

	int j = 0;
	for (int i = 0; i < strlen(my_string); i++) {
		if (my_string[i] == delimiter) {
			if (split == 0) {
				split = 1;
				continue;
			}
		}

		if (split == 0) {
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

// this function removes all new lines and carriage returns from a string
// you might want to write a new function that replaces '\r' and '\n'
// with a delimiter of user's choice
void remove_nl_and_cr(char raw_string[]) {
  char processed_string[strlen(raw_string)];

  // counter for num of elements of processed_string
  int j = 0;
  for (int i = 0; i<strlen(raw_string); i++) {
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

// remove new lines, carriage returns and spaces
void remove_whitespace(char raw_string[]) {
  char processed_string[strlen(raw_string)];

  // counter for num of elements of processed_string
  int j = 0;
  for (int i = 0; i<strlen(raw_string); i++) {
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

void remove_until_delim(char raw_string[], char delimiter, int occurence) {
	int chunk = 0;
	int j = 0;
	char *tmp_string = malloc(strlen(raw_string));
	memset(tmp_string, '\0', strlen(raw_string));

	for (int i = 0; i < strlen(raw_string); i++) {
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
