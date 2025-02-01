#include "../src/list_handling.h"
#include "../src/parse_ics.h"
#include <stdio.h>

int main() {
	// initialize empty list
	struct event *head = NULL;

	// 1
	printf("\nTesting tests/failed_cal.ics:\n\n");
	char *current_date = "20240710T113000";

	printf("DEBUG - current_date: %s\n\n", current_date);

	parse_ics_file("../../tests/failed_cal.ics", &head);

	print_upcoming(head, current_date, 0);

	// 2
	printf("\nTesting tests/calendar.ics:\n\n");
	parse_ics_file("../../tests/calendar.ics", &head);

	print_upcoming(head, current_date, 0);
}
