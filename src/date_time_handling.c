#include "date_time_handling.h"
#include "string_handling.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <assert.h>

// buffer needs to contain a string with a strlen of 15 (format: "xxxxxxxxTxxxxxx")
// or a strlen of 16 (format: "YYYYmmddTHHMMSSZ")
void get_date (char buffer[]) {
	// add 1 because strlen does not include the null character
	size_t buffer_size = strlen (buffer) + 1;
	time_t my_unix_ts = time (NULL);
	struct tm* my_tm_local = localtime (&my_unix_ts);
	if (strlen (buffer) == 15) {
		strftime (buffer, buffer_size, "%Y%m%dT%H%M%S", my_tm_local);
	}
	else if (strlen (buffer) == 16) {
		strftime (buffer, buffer_size, "%Y%m%dT%H%M%SZ", my_tm_local);
	}
}

// 20230823T194138 -> 2023-08-23 19:41:38
// 20230823T194138Z -> 2023-08-23 19:41:38
// 20241209 -> 2024-12-09
// caller has to free() the returned char array
char* pretty_date_time (char date_time[]) {
	// need one more char in the char pointer for null-termination
	int pdt_len = 20;
	if (!strchr (date_time, 'T')) {
		pdt_len = 11;
	}

	char* pretty_dt = malloc (pdt_len);
	memset(pretty_dt, '\0', pdt_len);
	int dt_counter = 0;

	if (!strcmp(date_time, "")) {
		return pretty_dt;
	}

	for (int i = 0; i < (pdt_len-1); i++) {
		if (i == 4 || i == 7) {
			pretty_dt[i] = '-';
			continue;
		}
		if (i == 13 || i == 16) {
			pretty_dt[i] = ':';
			continue;
		}

		if (date_time[dt_counter] == 'T') {
			pretty_dt[i] = ' ';
		} else {
			pretty_dt[i] = date_time[dt_counter];
		}
		dt_counter++;
	}

	// null-terminate string
	pretty_dt[strlen(pretty_dt)] = '\0';

	return pretty_dt;
}

void pretty_print_date_time (char date_time[]) {
	char* pdt = pretty_date_time(date_time);

	printf("%s", pdt);

	free(pdt);
}

void marshall_date_time (char date_time[]) {
	char transformed_string[strlen (date_time)];
	int j = 0;
	remove_nl_and_cr (date_time);
	for (size_t i = 0; i <= strlen (date_time); i++) {
		if (date_time[i] != ':' && date_time[i] != '-') {
			if (date_time[i] == ' ') {
				transformed_string[j] = 'T';
			}
			else {
				transformed_string[j] = date_time[i];
			}

			j++;
		}

	}
	memset (date_time, '\0', strlen (date_time));
	strcpy (date_time, transformed_string);
}

void print_end_date (char end_date[], char start_date[]) {
	time_t start_uts = transform_date_to_unix_ts (start_date);
	time_t end_uts = transform_date_to_unix_ts (end_date);
	double time_difference = difftime (end_uts, start_uts);

	// end_date is all day event
	if (strlen (end_date) == 8) {
		if (time_difference == 86400) {
			return;
		}
		else {
			printf (" - ");
			end_uts -= 86400;
			char* end_date_minus_one =
				transform_unix_ts_to_date (end_uts);
			pretty_print_date_time (end_date_minus_one);
			free (end_date_minus_one);
			return;
		}
	}
	else {
		// end_date is not an all day event

		char* end_date_chunk = strtok (end_date, "T");
		char* end_time_chunk = strtok (NULL, "T");
		char* start_date_chunk = strtok (start_date, "T");

		printf (" - ");

		// only print the end date if it is not the same as the start date
		if (strcmp (start_date_chunk, end_date_chunk) != 0) {
			printf ("%c%c%c%c-", end_date_chunk[0],
					end_date_chunk[1], end_date_chunk[2],
					end_date_chunk[3]);
			printf ("%c%c-", end_date_chunk[4],
					end_date_chunk[5]);
			printf ("%c%c ", end_date_chunk[6],
					end_date_chunk[7]);
		}

		printf ("%c%c:", end_time_chunk[0], end_time_chunk[1]);
		printf ("%c%c:", end_time_chunk[2], end_time_chunk[3]);
		printf ("%c%c", end_time_chunk[4], end_time_chunk[5]);
	}
}

// YYYYmmdd -> unix timestamp
time_t transform_date_to_unix_ts (char date_str[]) {
	time_t unix_stamp = 0;
	int date_only = atoi (date_str);
	struct tm my_tm = { 0 };
	my_tm.tm_year = date_only / 10000 - 1900;
	my_tm.tm_mon = (date_only % 10000) / 100 - 1;
	my_tm.tm_mday = date_only % 100;

	unix_stamp = mktime (&my_tm);

	return unix_stamp;
}

// unix timestamp -> YYYYmmdd
// make sure to free the returned buffer
char* transform_unix_ts_to_date (time_t unix_ts) {
	char* date_buffer = malloc (9);
	struct tm* my_tm;
	my_tm = localtime (&unix_ts);
	strftime (date_buffer, 9, "%Y%m%d", my_tm);

	return date_buffer;
}

char* get_tz () {
	char* timezone_path = malloc (256);
	ssize_t bytes_read = readlink ("/etc/localtime", timezone_path, 255);

	if (bytes_read != -1) {
		// Null-terminate the string
		timezone_path[bytes_read] = '\0';
	}
	else {
		perror ("readlink");
		exit (1);
	}

	return timezone_path;
}
