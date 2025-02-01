#include "../src/list_handling.h"
#include "../src/parse_ics.h"
#include <stdio.h>

int main() {
	// initialize empty list
	struct event *head = NULL;

	parse_ics_file("../../tests/calendar.ics", &head);

	parse_ics_file("../../tests/failed_cal.ics", &head);

	return 0;
}
