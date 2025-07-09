#include "../src/list_handling.h"
#include "../src/parse_ics.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main() {
	// initialize empty list
	struct event *head = NULL;

	parse_ics_file("../../test_files/calendar.ics", &head);

	// BUG DETECTED - remove carriage returns!
	assert(!strcmp(head->summary, "go for a walk\r"));

	parse_ics_file("../../test_files/failed_cal.ics", &head);

	return 0;
}
