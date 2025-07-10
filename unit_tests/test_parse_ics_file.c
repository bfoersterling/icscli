#include "../src/list_handling.h"
#include "../src/parse_ics.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int main() {
	// 1
	// initialize empty list
	struct event* head = NULL;

	parse_ics_file("../../test_files/calendar.ics", &head);

	assert(!strcmp(head->summary, "go for a walk"));

	// 2
	head = NULL;

	parse_ics_file("../../test_files/failed_cal.ics", &head);

	assert(!strcmp(head->summary, "Interview with John Doe"));

	return 0;
}
