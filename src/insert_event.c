#include "insert_event.h"
#include "string_handling.h"
#include "date_time_handling.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <uuid/uuid.h>

void insert_event(char *file_name) {
	int myfd = open(file_name, O_RDWR);
	bool all_day_event = false;
	char summary_buf[256] = "SUMMARY:";
	char *input_buffer = &summary_buf[8];
	uuid_t uuid;
	char uuid_str[37] = "";
	char dtstamp[] = "YYYYmmddTHHMMSSZ";
	char *time_zone = get_tz();
	char *dtstart_buffer = malloc(128);
	char *dtend_buffer = malloc(128);

	remove_until_delim(time_zone, '/', 4);

	printf("Insert a new event\n");

	printf("Is this an all day event? [y/n] ");
	all_day_event = binary_user_choice();

	printf("SUMMARY: ");
	fgets (input_buffer, (sizeof(summary_buf)-strlen(summary_buf)), stdin);

	if (strchr(input_buffer, '\n') == NULL)
		printf ("The input has been truncated to:\n%s\n", input_buffer);

	// modify the string to have \r\n line ending
	summary_buf[strlen(summary_buf)+1] = '\0';
	summary_buf[strlen(summary_buf)-1] = '\r';
	summary_buf[strlen(summary_buf)] = '\n';

	uuid_generate(uuid);
	// parse uuid to a string
	uuid_unparse(uuid, uuid_str);

	get_date(dtstamp);

	get_dtstart_dtend(dtstart_buffer, all_day_event, "start");
	marshall_date_time(dtstart_buffer);
	form_dtstart_string(dtstart_buffer, time_zone);

	get_dtstart_dtend(dtend_buffer, all_day_event, "end");
	marshall_date_time(dtend_buffer);
	form_dtend_string(dtend_buffer, time_zone);

	seek_cal_end(myfd);
	write(myfd, "BEGIN:VEVENT\r\n", strlen("BEGIN:VEVENT\r\n"));
	write(myfd, "UID:", strlen("UID:"));
	write(myfd, uuid_str, strlen(uuid_str));
	write(myfd, "\r\n", strlen("\r\n"));
	write(myfd, "DTSTAMP:", strlen("DTSTAMP:"));
	write(myfd, dtstamp, strlen(dtstamp));
	write(myfd, "\r\n", strlen("\r\n"));
	write(myfd, dtstart_buffer, strlen(dtstart_buffer));
	write(myfd, dtend_buffer, strlen(dtend_buffer));
	write(myfd, "SEQUENCE:2\r\n", strlen("SEQUENCE:2\r\n"));
	write(myfd, summary_buf, strlen(summary_buf));
	write(myfd, "TRANSP:OPAQUE\r\n", strlen("TRANSP:OPAQUE\r\n"));
	write(myfd, "CLASS:PUBLIC\r\n", strlen("CLASS:PUBLIC\r\n"));
	write(myfd, "CREATED:", strlen("CREATED:"));
	write(myfd, dtstamp, strlen(dtstamp));
	write(myfd, "\r\n", strlen("\r\n"));
	write(myfd, "LAST-MODIFIED:", strlen("LAST-MODIFIED:"));
	write(myfd, dtstamp, strlen(dtstamp));
	write(myfd, "\r\n", strlen("\r\n"));
	write(myfd, "END:VEVENT\r\n", strlen("END:VEVENT\r\n"));

	write(myfd, "END:VCALENDAR\r\n", strlen("END:VCALENDAR\r\n"));

	close(myfd);
	free(time_zone);
	free(dtstart_buffer);
	free(dtend_buffer);

	exit(0);
}

void seek_cal_end(int fd) {
	char search_string[] = "END:VCALENDAR";
	size_t j = 0;
	char char_reader = '\0';

	lseek(fd, -1, SEEK_END);

	while(read(fd, &char_reader, 1)) {
		// no need to compare to the null terminator of the search_string
		if (char_reader == search_string[strlen(search_string)-j-1]) {
			j++;
		} else {
			j = 0;
		}
		if (j == (strlen(search_string))) {
			lseek(fd, -1, SEEK_CUR);
			break;
		}
		lseek(fd, -2, SEEK_CUR);
	}
}

bool binary_user_choice() {
	char input_buffer[64] = "";
	if (fgets (input_buffer, sizeof(input_buffer), stdin) == NULL) {
		printf ("an fgets error occured\n");
	}
	if (! strchr(input_buffer, '\n')) {
		printf ("Input buffer overflow!\n");
		exit(1);
	}
	if (input_buffer[0] == 'n' || input_buffer[0] == 'N') {
		return false;
	} else if (input_buffer[0] == 'y' || input_buffer[0] == 'Y') {
		return true;
	} else {
		printf ("Please enter a N/n or Y/y character!\n");
		exit(1);
	}
}

// char *start_or_end should contain "start" or "end"
void get_dtstart_dtend(char input_buffer[], bool all_day_event, char *start_or_end) {
	if (all_day_event) {
		printf("Enter the %s date in YYYY-mm-dd format!\n", start_or_end);
		if (fgets(input_buffer, 128, stdin) == NULL) {
			perror ("fgets");
			exit(1);
		}
		if (strlen(input_buffer) != 11) {
			printf ("Wrong format!\n");
			exit(1);
		}
	} else {
		printf("Enter the %s date in YYYY-mm-dd HH:MM:SS format!\n", start_or_end);
		if (fgets(input_buffer, 128, stdin) == NULL) {
			perror ("fgets");
			exit(1);
		}
		if (strlen(input_buffer) != 20) {
			printf ("Wrong format!\n");
			exit(1);
		}
	}
}

void form_dtstart_string(char dtstart_buffer[], char time_zone[]) {
	char dtstart_copy[strlen(dtstart_buffer)];
	strcpy(dtstart_copy, dtstart_buffer);

	// not all day event
	if (strlen(dtstart_buffer) == 15) {
		strcpy(dtstart_buffer, "DTSTART;TZID=/freeassociation.sourceforge.net");
		strcat(dtstart_buffer, time_zone);
		strcat(dtstart_buffer, ":\r\n ");
		strcat(dtstart_buffer, dtstart_copy);
	} else {
		// all day event
		strcpy(dtstart_buffer, "DTSTART;VALUE=DATE:");
		strcat(dtstart_buffer, dtstart_copy);
	}
	strcat(dtstart_buffer, "\r\n");
}

void form_dtend_string(char dtend_buffer[], char time_zone[]) {
	char dtend_copy[strlen(dtend_buffer)];
	strcpy(dtend_copy, dtend_buffer);

	// not all day event
	if (strlen(dtend_buffer) == 15) {
		strcpy(dtend_buffer, "DTEND;TZID=/freeassociation.sourceforge.net");
		strcat(dtend_buffer, time_zone);
		strcat(dtend_buffer, ":\r\n ");
		strcat(dtend_buffer, dtend_copy);
	} else {
		// all day event
		strcpy(dtend_buffer, "DTEND;VALUE=DATE:");
		strcat(dtend_buffer, dtend_copy);
	}
	strcat(dtend_buffer, "\r\n");
}
