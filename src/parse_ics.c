#include "file_handling.h"
#include "list_handling.h"
#include "parse_ics.h"
#include "string_handling.h"
#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void parse_event(char event_string[], struct event **head) {
	char *start_date = strstr(event_string, "\nDTSTART");
	char *end_date = strstr(event_string, "\nDTEND");
	char *summary = strstr(event_string, "\nSUMMARY");
	summary = strchr(summary, ':') + 1;

	char *start_date_str = malloc(256);
	char *end_date_str = malloc(256);
	char *summary_str = malloc(512);

	memset(start_date_str, '\0', 256);
	memset(end_date_str, '\0', 256);
	memset(summary_str, '\0', 512);

	assert(start_date != NULL);
	assert(end_date != NULL);
	assert(summary != NULL);

	strncpy(start_date_str, start_date,
			strchr(start_date + 1, '\n') - start_date);

	strncpy(end_date_str, end_date, strchr(end_date + 1, '\n') - end_date);

	strncpy(summary_str, summary, strchr(summary + 1, '\n') - summary);
	trim_space(summary_str);

	// parse dates
	remove_whitespace(start_date_str);
	cut_string(start_date_str, ':', 1);

	remove_whitespace(end_date_str);
	cut_string(end_date_str, ':', 1);

	sorted_insert(head, start_date_str, end_date_str, summary_str);

	free(start_date_str);
	free(end_date_str);
	free(summary_str);
}

// the unfolded string has a space
// as a separator between what were previously separate lines
void unfolding_string(char *folded_string, char *unfolded_string) {
	int j = 0;
	for (size_t i = 0; i < strlen(folded_string); i++) {
		if (folded_string[i] == '\r' && folded_string[i + 1] == '\n'
				&& isblank(folded_string[i + 2])) {
			i += 3;
			while (isblank(folded_string[i])) {
				i++;
			}
			unfolded_string[j] = ' ';
			j++;
			unfolded_string[j] = folded_string[i];
			j++;
		} else {
			unfolded_string[j] = folded_string[i];
			j++;
		}
	}
}

/* this function takes the head of an empty initialized event list
 * and the path to the ics file
 * it will "fill" the list
 */
void parse_ics_file(char *file_path, struct event **head) {
	char my_event[8192] = "";
	char unfolded_event[8192] = "";

	int myfd = open(file_path, O_RDONLY);
	if (myfd == -1) {
		perror ("Error opening file");
		exit(1);
	}

	while(read_until_nl(myfd, my_event)) {
		if (strncmp(my_event, "BEGIN:VEVENT", 12) == 0) {
			// include the BEGIN:EVENT to not loose the new line of first field
			lseek(myfd, -1, SEEK_CUR);
			memset(my_event, '\0', sizeof(my_event));
			read_until_string(myfd, my_event, "END:VEVENT");
			unfolding_string(my_event, unfolded_event);
			parse_event(unfolded_event, head);
		}
		memset(my_event, '\0', sizeof(my_event));
	}

	close(myfd);
}
