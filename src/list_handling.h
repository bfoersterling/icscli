#pragma once

struct event {
  char summary[256];
  char start_date[256];
  char end_date[256];
  struct event *next;
};

void print_list(struct event *head);
void sorted_insert(struct event **head, char start_date[], char end_date[], char summary[]);
void free_list(struct event *head);
void print_upcoming(struct event *head, char current_date[], int show_all_events);
