#include "insert_event.h"
#include "cli_arg_parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void usage() {
	printf ("-a\t\t\tshow all upcoming events (default is 5 events)\n");
	printf ("-f [FILE PATH]\t\tspecify ics file path\n");
	printf ("-h\t\t\tprint this help\n");
	printf ("-i\t\t\tinsert an event\n");
	exit(0);
}

void get_cli_args(int argc, char **argv, char **file_name, int *show_all_events) {
	int opt = 0;

	memset(file_name, '\0', strlen(*file_name));

	char *home = getenv("HOME");
	*file_name = home;

	if (home != NULL) {
	  strcat(*file_name, "/.local/share/evolution/calendar/system/calendar.ics");
	} else {
	  printf ("Environment variable HOME is not set.\n");
	  exit(1);
	}

	while ((opt = getopt(argc, argv, "f:ahi")) != -1) {
    	switch(opt) {
			case 'a':
			*show_all_events = 1;
			break;
			case 'f':
			*file_name = optarg;
			break;
			case 'h':
			usage();
			break;
			case 'i':
			insert_event(*file_name);
			break;
    	}
	}
}
