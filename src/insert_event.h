#pragma once

void insert_event(char *file_name);
void seek_cal_end(int fd);
int binary_user_choice();
void get_dtstart_dtend(char input_buffer[], int all_day_event, char *start_or_end);
void form_dtstart_string(char dtstart_buffer[], char time_zone[]);
void form_dtend_string(char dtend_buffer[], char time_zone[]);
