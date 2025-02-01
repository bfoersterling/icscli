#pragma once

#include <time.h>
#include <string.h>

void get_date(char buffer[]);
char *get_tz();
char* pretty_date_time(char date_time[]);
void pretty_print_date_time(char date_time[]);
void marshall_date_time(char date_time[]);
void print_end_date(char end_date[], char start_date[]);
time_t transform_date_to_unix_ts(char date_str[]);
char *transform_unix_ts_to_date(time_t unix_ts);
