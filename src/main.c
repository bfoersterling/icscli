#include "list_handling.h"
#include "parse_ics.h"
#include "cli_arg_parsing.h"
#include "date_time_handling.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	char *ics_path = malloc(256);
	ics_path = memset(ics_path, '\0', 256);

	bool show_all_events = false;

	get_cli_args(argc, argv, &ics_path, &show_all_events);

	static char current_date[] = "xxxxxxxxTxxxxxx";
	get_date(current_date);
	printf ("Current date and time: ");
	pretty_print_date_time(current_date);
	printf ("\n\n");

	// initialize linked list
	struct event *head = NULL;

	parse_ics_file(ics_path, &head);

	print_upcoming(head, current_date, show_all_events);

	free_list(head);

	free(ics_path);

	return 0;
}
