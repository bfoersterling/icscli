#pragma once

void parse_event(char event_string[], struct event **head);
void unfolding_string(char* folded_string, char* unfolded_string);
void parse_ics_file(char *file_path, struct event **head);
